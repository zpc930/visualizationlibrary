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

#ifndef MultiDrawElements_INCLUDE_ONCE
#define MultiDrawElements_INCLUDE_ONCE

#include <vl/Primitives.hpp>
#include <vl/Array.hpp>
#include <vl/Log.hpp>
#include <vl/Say.hpp>
#include <algorithm>

namespace vl
{
  //------------------------------------------------------------------------------
  // MultiDrawElements
  //------------------------------------------------------------------------------
  /** 
   * Wrapper for the OpenGL function glMultiDrawElements(), see also http://www.opengl.org/sdk/docs/man/xhtml/glMultiDrawElements.xml for more information.
   *
  */
  template <typename index_type, GLenum Tgltype, class arr_type>
  class MultiDrawElements: public Primitives
  {
  public:
    virtual const char* className() { return "MultiDrawElements"; }

    MultiDrawElements(EPrimitiveType primitive = PT_TRIANGLES)
    {
      #ifndef NDEBUG
        mObjectName = className();
      #endif
      mType                    = primitive;
      mIndexBuffer             = new arr_type;
      mPrimitiveRestartIndex   = ~(index_type)0;
      mPrimitiveRestartEnabled = false;
    }

    MultiDrawElements& operator=(const MultiDrawElements& other)
    {
      Primitives::operator=(other);
      *indices() = *other.indices();
      mPrimitiveRestartEnabled = other.mPrimitiveRestartEnabled;
      mPrimitiveRestartIndex   = other.mPrimitiveRestartIndex;
      setCountVector(other.mCountVector);
      return *this;
    }

    virtual ref<Primitives> clone() const 
    { 
      ref<MultiDrawElements> de = new MultiDrawElements;
      *de = *this;
      return de;
    }

    virtual unsigned int handle() const { return indices()->gpuBuffer()->handle(); }

    virtual size_t indexCount() const { return indices()->size(); }

    virtual size_t indexCountGPU() const { return indices()->sizeGPU(); }

    virtual size_t index(int i) const { return (int)indices()->at(i); }

    arr_type* indices() { return mIndexBuffer.get(); }
    const arr_type* indices() const { return mIndexBuffer.get(); }

    virtual void updateVBOs(bool discard_local_data = false)
    {
      indices()->updateVBO(discard_local_data);
    }

    virtual void deleteVBOs()
    {
      indices()->gpuBuffer()->deleteGLBufferObject();
    }

    virtual void clearLocalBuffer()
    {
      indices()->gpuBuffer()->resize(0);
    }

    /** Returns the number of triangles contained in this primitive set.
      * \note This function returns -1 if primitive restart is enabled. */
    int triangleCount() const
    {
      if (primitiveRestartEnabled())
        return -1;

      int total_count = 0;
      for(size_t i=0; i<mCountVector.size(); ++i)
      {
        size_t count = mCountVector[i];
        switch( mType )
        {
          case PT_TRIANGLES: total_count += (count / 3);
          case PT_TRIANGLE_STRIP: total_count += (count - 2);
          case PT_TRIANGLE_FAN: total_count += (count - 2);
          case PT_QUADS: total_count += (count / 4 * 2);
          case PT_QUAD_STRIP: total_count += ( (count - 2) / 2 ) * 2;
          case PT_POLYGON: total_count += (count - 2);
          case PT_POINTS:
          case PT_LINES:
          case PT_LINE_LOOP:
          case PT_LINE_STRIP:
          default:
            break;
        }
      }

      return total_count;
    }

    /** Returns the number of lines contained in this primitive set.
      * \note This function returns -1 if primitive restart is enabled. */
    int lineCount() const 
    {
      if (primitiveRestartEnabled())
        return -1;

      int total_count = 0;
      for(size_t i=0; i<mCountVector.size(); ++i)
      {
        size_t count = mCountVector[i];
        switch( mType )
        {
          case PT_LINES:      total_count += count / 2;
          case PT_LINE_LOOP:  total_count += count;
          case PT_LINE_STRIP: total_count += count - 1;
          default:
            break;
        }
      }

      return total_count;
    }

    /** Returns the number of points contained in this primitive set.
      * \note This function returns -1 if primitive restart is enabled. */
    int pointCount() const
    {
      if (primitiveRestartEnabled())
        return -1;

      int total_count = 0;
      for(size_t i=0; i<mCountVector.size(); ++i)
      {
        size_t count = mCountVector[i];
        switch( mType )
        {
        case PT_POINTS: total_count += count;
        default:
          break;
        }
      }

      return total_count;
    }

    /** Returns always false. */
    virtual bool getTriangle( size_t, unsigned int*) const
    {
      return false;
    }

    virtual void render(bool use_vbo) const
    {
      VL_CHECK(GLEW_VERSION_1_4);
      VL_CHECK(!use_vbo || (use_vbo && (GLEW_ARB_vertex_buffer_object||GLEW_VERSION_1_5||GLEW_VERSION_3_0)))
      use_vbo &= GLEW_ARB_vertex_buffer_object||GLEW_VERSION_1_5||GLEW_VERSION_3_0; // && indices()->gpuBuffer()->handle() && indexCountGPU();
      if ( !use_vbo && !indexCount() )
        return;

      // primitive restart enable
      if(primitiveRestartEnabled())
      {
        if(GLEW_VERSION_3_1)
        {
          glEnable(GL_PRIMITIVE_RESTART);
          glPrimitiveRestartIndex(primitiveRestartIndex());
        }
        else
        if(GLEW_NV_primitive_restart)
        {
          glEnable(GL_PRIMITIVE_RESTART_NV);
          glPrimitiveRestartIndexNV(primitiveRestartIndex());
        }
        else
        {
          vl::Log::error("MultiDrawElements error: primitive restart not supported by this OpenGL implementation!\n");
          VL_TRAP();
          return;
        }
      }

      if (use_vbo && indices()->gpuBuffer()->handle())
      {
        VL_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices()->gpuBuffer()->handle());
      }
      else
        VL_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      if (use_vbo)
      {
        glMultiDrawElements( 
          primitiveType(), 
          (GLsizei*)&mCountVector[0], 
          indices()->glType(), 
          (const GLvoid**)&mNULLPointerVector[0], mCountVector.size() 
        );
      }
      else
      {
        glMultiDrawElements( 
          primitiveType(), 
          (GLsizei*)&mCountVector[0], 
          indices()->glType(), 
          (const GLvoid**)&mPointerVector[0], mCountVector.size() 
        );
      }

      // primitive restart disable
      if(primitiveRestartEnabled())
      {
        if(GLEW_VERSION_3_1)
          glDisable(GL_PRIMITIVE_RESTART);
        else
        if(GLEW_NV_primitive_restart)
          glDisable(GL_PRIMITIVE_RESTART_NV);
      }

      if (use_vbo && this->indices()->gpuBuffer()->handle())
        VL_glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }

    /** Sets the vector defining the length of each primitive and automatically computes the pointer 
      * vectors used to exectue glMultiDrawElements(). */
    void setCountVector(const std::vector<GLsizei>& vcount)
    {
      mCountVector = vcount;

      // set all to null: used when VBO is active.
      mNULLPointerVector.resize( vcount.size() );

      // used when VBOs are not active.
      mPointerVector.clear();
      const index_type* ptr = (const index_type*)indices()->gpuBuffer()->ptr();
      for(size_t i=0; i<vcount.size(); ++i)
      {
        mPointerVector.push_back(ptr);
        ptr += vcount[i];
      }
      VL_CHECK( ptr - (const index_type*)indices()->gpuBuffer()->ptr() <= indexCount() );
    }

    /** The count vector used as 'count' parameter of glMultiDrawElements. */
    const std::vector<unsigned int>& countVector() const { return mCountVector; }

    /** The pointer vector used as 'indices' parameter of glMultiDrawElements. */
    const std::vector<index_type*>& pointerVector() const { return mPointerVector; }

    /** Returns the special index which idendifies a primitive restart. By default it is set to ~0 that is 0xFF, 0xFFFF, 0xFFFFFFFF respectively for ubyte, ushort, uint types. */
    GLuint primitiveRestartIndex() const { return mPrimitiveRestartIndex; }
    /** Sets the special index which idendifies a primitive restart. By default it is set to ~0 that is 0xFF, 0xFFFF, 0xFFFFFFFF respectively for ubyte, ushort, uint types. */
    void setPrimitiveRestartIndex(GLuint index) { mPrimitiveRestartIndex = index; }

    /** Returns whether the primitive-restart functionality is enabled or not. See http://www.opengl.org/registry/specs/NV/primitive_restart.txt */
    bool primitiveRestartEnabled() const { return mPrimitiveRestartEnabled; }
    
    /** Enables the primitive-restart functionality. See http://www.opengl.org/registry/specs/NV/primitive_restart.txt
      * \note Functions like triangleCount(), lineCount(), pointCount() and sortTriangles() should not be used when primitive restart is enabled. */
    void setPrimitiveRestartEnabled(bool enabled) { mPrimitiveRestartEnabled = enabled; }

  protected:
    ref< arr_type > mIndexBuffer;
    GLuint mPrimitiveRestartIndex;
    bool mPrimitiveRestartEnabled;

    std::vector<GLsizei>           mCountVector;
    std::vector<const index_type*> mPointerVector;
    std::vector<const index_type*> mNULLPointerVector;
  };
  //------------------------------------------------------------------------------
  // typedefs
  //------------------------------------------------------------------------------
  /** A MultiDrawElements using indices of type \p GLuint. */
  typedef MultiDrawElements<GLuint, GL_UNSIGNED_INT, ArrayUInt> MultiDrawElementsUInt;
  //------------------------------------------------------------------------------
  /** A MultiDrawElements using indices of type \p GLushort. */
  typedef MultiDrawElements<GLushort, GL_UNSIGNED_SHORT, ArrayUShort> MultiDrawElementsUShort;
  //------------------------------------------------------------------------------
  /** A MultiDrawElements using indices of type \p GLubyte. */
  typedef MultiDrawElements<GLubyte, GL_UNSIGNED_BYTE, ArrayUByte> MultiDrawElementsUByte;
  //------------------------------------------------------------------------------
}

#endif
