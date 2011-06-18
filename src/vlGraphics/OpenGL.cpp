/**************************************************************************************/
/*                                                                                    */
/*  Visualization Library                                                             */
/*  http://www.visualizationlibrary.com                                               */
/*                                                                                    */
/*  Copyright (c) 2005-2010, Michele Bosi                                             */
/*  All rights reserved.                                                              */
/*                                                                                    */
/*  Redistribution and use in source and binary forms, with or without modification,  */
/*  are permitted provided that the following conditions are met:                     */
/*                                                                                    */
/*  - Redistributions of source code must retain the above copyright notice, this     */
/*  list of conditions and the following disclaimer.                                  */
/*                                                                                    */
/*  - Redistributions in binary form must reproduce the above copyright notice, this  */
/*  list of conditions and the following disclaimer in the documentation and/or       */
/*  other materials provided with the distribution.                                   */
/*                                                                                    */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND   */
/*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED     */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE            */
/*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR  */
/*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    */
/*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      */
/*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON    */
/*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT           */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS     */
/*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      */
/*                                                                                    */
/**************************************************************************************/

#include <vlGraphics/OpenGL.hpp>
#include <vlCore/String.hpp>
#include <vlCore/Log.hpp>
#include <vlCore/Say.hpp>
#include <algorithm>

namespace vl
{
  bool Has_GL_Version_1_1 = false;
  bool Has_GL_Version_1_2 = false;
  bool Has_GL_Version_1_3 = false;
  bool Has_GL_Version_1_4 = false;
  bool Has_GL_Version_1_5 = false;
  bool Has_GL_Version_2_0 = false;
  bool Has_GL_Version_2_1 = false;
  bool Has_GL_Version_3_0 = false;
  bool Has_GL_Version_3_1 = false;
  bool Has_GL_Version_3_2 = false;
  bool Has_GL_Version_3_3 = false;
  bool Has_GL_Version_4_0 = false;
  bool Has_GL_Version_4_1 = false;

  #define VL_EXTENSION(extension) bool Has_##extension = false;
  #include "GLExtensionList.inc"
  #undef VL_EXTENSION
}

void vl::initOpenGLVersions()
{
    // clear errors
    glGetError();
    // test if fixed function pipeline is supported.
    glDisable(GL_LIGHTING);
    // check error code
    bool compatible = glGetError() == GL_NO_ERROR;
    const char* version_str = (const char*)glGetString(GL_VERSION);
    int vmaj = version_str[0] - '0';
    int vmin = version_str[2] - '0';
    int version = vmaj*10 + vmin;

    Has_GL_Version_1_1 = vmaj == 1 && vmin >= 1 || vmaj == 2 || version == 30 || (vmaj > 1 && compatible);
    Has_GL_Version_1_2 = vmaj == 1 && vmin >= 2 || vmaj == 2 || version == 30 || (vmaj > 1 && compatible);
    Has_GL_Version_1_3 = vmaj == 1 && vmin >= 3 || vmaj == 2 || version == 30 || (vmaj > 1 && compatible);
    Has_GL_Version_1_4 = vmaj == 1 && vmin >= 4 || vmaj == 2 || version == 30 || (vmaj > 1 && compatible);
    Has_GL_Version_1_5 = vmaj == 1 && vmin >= 5 || vmaj == 2 || version == 30 || (vmaj > 1 && compatible);
    Has_GL_Version_2_0 = vmaj == 2 && vmin >= 0 || version == 30 || (vmaj > 2 && compatible);
    Has_GL_Version_2_1 = vmaj == 2 && vmin >= 1 || version == 30 || (vmaj > 2 && compatible);
    Has_GL_Version_3_0 = vmaj == 3 && vmin >= 0 || (vmaj > 3 && compatible);
    Has_GL_Version_3_1 = vmaj == 3 && vmin >= 1 || (vmaj > 3 && compatible);
    Has_GL_Version_3_2 = vmaj == 3 && vmin >= 2 || (vmaj > 3 && compatible);
    Has_GL_Version_3_3 = vmaj == 3 && vmin >= 3 || (vmaj > 3 && compatible);
    Has_GL_Version_4_0 = vmaj == 4 && vmin >= 0 || (vmaj > 4 && compatible);
    Has_GL_Version_4_1 = vmaj == 4 && vmin >= 1 || (vmaj > 4 && compatible);

    std::string extensions;
    if (Has_GL_Version_3_0||Has_GL_Version_4_0)
    {
      int count = 0;
      glGetIntegerv(GL_NUM_EXTENSIONS, &count);
      for( int i=0; i<count; ++i )
      {
        const char* str = (const char*)glGetStringi(GL_EXTENSIONS,i); VL_CHECK_OGL();
        extensions += std::string(str) + " ";
      }
    }
    else
    {
      VL_CHECK(glGetString(GL_EXTENSIONS));
      extensions = (const char*)glGetString(GL_EXTENSIONS);
    }

    #define INIT_EXTENSION(extension) Has_##extension=checkExtension("|GL_"#extension"|", extensions.c_str())

    struct CheckExtension
    {
      bool operator()(const char* ext_name, const char* list)
      {
        size_t len = strlen(ext_name);
        const char* ext = list;
        const char* ext_end = ext + strlen(ext);

        for( const char* pos = strstr(ext,ext_name); pos && pos < ext_end; pos = strstr(pos,ext_name) )
        {
          if (pos[len] == ' ' || pos[len] == 0)
            return true;
          else
            pos += len;
        }

        return false;
      }

    } checkExtension;

    #define VL_EXTENSION(extension) Has_##extension = checkExtension(#extension, extensions.c_str());
    #include "GLExtensionList.inc"
    #undef VL_EXTENSION
}

//------------------------------------------------------------------------------
int vl::glcheck(const char* file, int line)
{
  unsigned int glerr = glGetError();
  // if an OpenGL context is available this must be clear!
  if ( glGetError() )
  {
    Log::bug( Say("%s:%n: NO OPENGL CONTEXT ACTIVE!\n") << file << line );
  }
  else
  if (glerr != GL_NO_ERROR)
  {
    String msg( (char*)gluErrorString(glerr) );
    Log::bug( Say("glGetError() [%s:%n]: %s\n") << file << line << msg );
  }
  return glerr;
}
//------------------------------------------------------------------------------
