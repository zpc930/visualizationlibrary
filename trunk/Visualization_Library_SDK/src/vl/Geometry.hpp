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

#ifndef Geometry_INCLUDE_ONCE
#define Geometry_INCLUDE_ONCE

#include <vl/IVertexAttribSet.hpp>
#include <vl/GLBufferObject.hpp>
#include <vl/Vector2.hpp>
#include <vl/Vector4.hpp>
#include <vl/Renderable.hpp>
#include <vl/vlnamespace.hpp>
#include <vl/Log.hpp>
#include <vl/Say.hpp>
#include <vlut/Colors.hpp>
#include <vl/DrawElements.hpp>
#include <vl/DrawArrays.hpp>
#include <vl/Collection.hpp>
#include <vl/VertexAttribInfo.hpp>

namespace vl
{
  class OpenGLContext;

  //------------------------------------------------------------------------------
  // Geometry
  //------------------------------------------------------------------------------
  /**
   * The Geometry class is a Renderable that implements a polygonal mesh made of
   * polygons, lines and points.
   *
   * \sa 
   * - ArrayAbstract
   * - Renderable
   * - Actor
   * - Transform
   * - Effect
  */
  class Geometry: public Renderable, public IVertexAttribSet
  {
  private:
    class TextureArray: public Object
    {
    public:
      TextureArray(int unit, ArrayAbstract* data): mTextureUnit(unit), mTexCoordArray(data) {}
      int mTextureUnit;
      ref<ArrayAbstract> mTexCoordArray;
      const GLBufferObject* gpuBuffer() const { return mTexCoordArray->gpuBuffer(); }
      GLBufferObject* gpuBuffer() { return mTexCoordArray->gpuBuffer(); }
    };

  public:
    virtual const char* className() { return "Geometry"; }
    
    /** Constructor. */
    Geometry();

    /** Destructor. */
    virtual ~Geometry();

    /**
     * Performs a shallow copy (as opposed to a deep copy) of the specified Geometry.
     * \sa deepCopy() */
    ref<Geometry> shallowCopy();

    /**
     * Performs a shallow copy (as opposed to a deep copy) of the specified Geometry.
     * \sa deepCopy() */
    void shallowCopy(Geometry*);

    /**
     * Performs a deep copy (as opposed to a shallow copy) of the specified Geometry.
     * \sa shallowCopy() */
    ref<Geometry> deepCopy() const;

    /**
     * Performs a deep copy (as opposed to a shallow copy) of the specified Geometry.
     * \sa shallowCopy() */
    void deepCopy(Geometry* ) const;

    //! Performs a shallowCopy() of the Geometry
    Geometry& operator=(const Geometry& other);

    virtual void render(const Actor* actor, const Shader* shader, const Camera* camera, OpenGLContext* gl_context) const;

    //! Returns the list of DrawCall objects bound to a Geometry
    Collection<DrawCall>* drawCalls() { return &mDrawCalls; }

    //! Returns the list of DrawCall objects bound to a Geometry
    const Collection<DrawCall>* drawCalls() const { return &mDrawCalls; }

    //! Geometry normal used when no normal array is defined.
    void setNormal(const fvec3& normal) { mNormal = normal; }

    //! Geometry normal used when no normal array is defined.
    const fvec3& normal() { return mNormal; }

    //! Geometry color used when no color array is defined.
    void setColor(const fvec4& color) { mColor = color; }

    //! Geometry color used when no color array is defined.
    const fvec4& color() { return mColor; }

    //! Geometry color used when no color array is defined.
    void setSecondaryColor(const fvec4& color) { mSecondaryColor = color; }

    //! Geometry color used when no color array is defined.
    const fvec4& secondaryColor() { return mSecondaryColor; }

    // ------------------------------------------------------------------------
    // --- Vertex Array Manipulation ---
    // ------------------------------------------------------------------------

    /**
     * Computes the normals in a "smooth" way, i.e. averaging the normals of those 
     * polygons that share one or more vertices.
     *
     * This function computes smoothed normals for triangle primitives and leaves 
     * unchanged the normals of line and point primitives when possible, i.e. when 
     * they don't share vertices with the polygonal primitives.
     *
     * \note 
     * This function modifies the local buffers. After calling this you might want 
     * to update the buffers allocated on the GPU.
    */
    void computeNormals();

    /** 
    * Transforms vertices and normals belonging to this geometry.
    * If 'normalize' == true the normals are normalized after being transformed
    * \note This functions supports every possible vertex format, type and layout.
    * \sa
    *  - ArrayAbstract::transform()
    *  - ArrayAbstract::normalize()
    *  - ArrayAbstract::computeBoundingSphere()
    *  - ArrayAbstract::computeBoundingBox()
    */
    void transform(const mat4&matr, bool normalize = true);

    /** Removes all the previously installed arrays. */
    virtual void clearArrays(bool clear_draw_calls=true);

    /** Updates all the vertex buffer objects of both vertex arrays and draw calls. */
    void updateVBOs(bool discard_local_data=false, bool force_update=false);

    /** Deletes all the vertex buffer objects of both vertex arrays and draw calls. */
    void deleteVBOs();

    // ------------------------------------------------------------------------
    // --- Geometry Utils --- 
    // ------------------------------------------------------------------------

    //! Merges all the PT_TRIANGLE_STRIP DrawElementsUInt objects into one single PT_TRIANGLE_STRIP DrawElementsUInt.
    void mergeTriangleStrips();

    //! Converts all the DrawCall objects bound to a Geometry into DrawArrays.
    void convertDrawCallToDrawArrays();

    //! Sorts the vertices of the geometry to maximize vertex-cache coherency.
    //! This function will work only if all the DrawCall are DrawElements.
    //! \returns true if all the DrawCall are DrawElements and the sorting took place.
    bool sortVertices();

    //! Assigns a random color to each vertex of each DrawCall object. If a vertex is shared among more than one DrawCall object its color is undefined.
    void colorizePrimitives();

    void regenerateVertices(const std::vector<size_t>& map_new_to_old);

    // mic fixme: move where appropriate: GUtils
    //! Computes the tangent (and optionally bitangent) vectors used to form a TBN matrix to be used for bumpmapping.
    //! @param vert_count The number of elements stored in @a vertex, @a normal, @a texcoord, @a tangent and @a bitangent.
    //! @param vertex Array containing the vertex positions.
    //! @param normal Array containing the normals of the vertices.
    //! @param texcoord Array containing the 2d texture coordinates of the bumpmap.
    //! @param primitives The triangles, quads etc. defining the geometry of the object.
    //! @param tangent [out] Returns the tangent vector of the vertices. This parameter is mandatory.
    //! @param bitangent [out] Returns the bitangent vector of the vertics. This parameter can be NULL.
    // Based on:
    // Lengyel, Eric. �Computing Tangent Space Basis Vectors for an Arbitrary Mesh�. Terathon Software 3D Graphics Library, 2001. 
    // http://www.terathon.com/code/tangent.html
    static void computeTangentSpace(
      size_t vert_count, 
      const vl::fvec3 *vertex, 
      const vl::fvec3* normal,
      const vl::fvec2 *texcoord, 
      const vl::DrawCall* primitives,
      vl::fvec3 *tangent, 
      vl::fvec3 *bitangent );

    // ------------------------------------------------------------------------
    // --- IVertexAttribSet Interface Implementation ---
    // ------------------------------------------------------------------------

    void setVertexArray(ArrayAbstract* data);

    const ArrayAbstract* vertexArray() const { return mVertexArray.get(); }

    ArrayAbstract* vertexArray() { return mVertexArray.get(); }

    void setNormalArray(ArrayAbstract* data);

    const ArrayAbstract* normalArray() const { return mNormalArray.get(); }

    ArrayAbstract* normalArray() { return mNormalArray.get(); }

    void setColorArray(ArrayAbstract* data);

    const ArrayAbstract* colorArray() const { return mColorArray.get(); }

    ArrayAbstract* colorArray() { return mColorArray.get(); }

    void setSecondaryColorArray(ArrayAbstract* data);

    const ArrayAbstract* secondaryColorArray() const { return mSecondaryColorArray.get(); }

    ArrayAbstract* secondaryColorArray() { return mSecondaryColorArray.get(); }

    void setFogCoordArray(ArrayAbstract* data);

    const ArrayAbstract* fogCoordArray() const { return mFogCoordArray.get(); }

    ArrayAbstract* fogCoordArray() { return mFogCoordArray.get(); }

    void setTexCoordArray(int tex_unit, ArrayAbstract* data);

    const ArrayAbstract* texCoordArray(int tex_unit) const
    { 
      for(int i=0; i<mTexCoordArrays.size(); ++i)
        if (mTexCoordArrays.at(i)->mTextureUnit == tex_unit)
          return mTexCoordArrays.at(i)->mTexCoordArray.get();
      return NULL;
    }

    ArrayAbstract* texCoordArray(int tex_unit) 
    { 
      for(int i=0; i<mTexCoordArrays.size(); ++i)
        if (mTexCoordArrays.at(i)->mTextureUnit == tex_unit)
          return mTexCoordArrays.at(i)->mTexCoordArray.get();
      return NULL;
    }

    int texCoordArrayCount() const { return mTexCoordArrays.size(); }

    void getTexCoordArrayAt(int i, int& out_tex_unit, const ArrayAbstract* &tex_array) const
    {
      VL_CHECK(i<mTexCoordArrays.size());
      out_tex_unit = mTexCoordArrays[i]->mTextureUnit;
      tex_array = mTexCoordArrays[i]->mTexCoordArray.get();
    }

    void setVertexAttribArray(unsigned int attrib_idx, bool normalize, EVertexAttribBehavior data_behav, ArrayAbstract* data) { setVertexAttribArray(VertexAttribInfo(attrib_idx, normalize, data_behav, data)); }

    void setVertexAttribArray(const VertexAttribInfo& info);

    const ArrayAbstract* vertexAttrib(unsigned int attrib_idx) const;

    ArrayAbstract* vertexAttrib(unsigned int attrib_idx);

    const VertexAttribInfo* vertexAttribInfo(unsigned int attrib_idx) const;

    VertexAttribInfo* vertexAttribInfo(unsigned int attrib_idx);

    ref<VertexAttribInfo> eraseVertexAttrib(unsigned int attrib_idx);

    int vertexAttribInfoCount() const { return mVertexAttribArrays.size(); }
    
    const VertexAttribInfo* getVertexAttribInfoAt(int i) const { return mVertexAttribArrays[i].get(); }

    /** The list of VertexAttribInfo objects bound to a Geometry. */
    Collection<VertexAttribInfo>* vertexAttribArrays() { return &mVertexAttribArrays; }

    /** The list of VertexAttribInfo objects bound to a Geometry. */
    const Collection<VertexAttribInfo>* vertexAttribArrays() const { return &mVertexAttribArrays; }

  protected:
    virtual void computeBounds_Implementation();

    // render calls
    Collection<DrawCall> mDrawCalls;

    // geometry color when no color array is defined
    fvec4 mColor;

    // geometry color when no color array is defined
    fvec4 mSecondaryColor;

    // normal when no normal array is defined
    fvec3 mNormal;

    //  --- IVertexAttribSet interface concrete implementation ---

    // conventional vertex attributes
    ref<ArrayAbstract> mVertexArray;
    ref<ArrayAbstract> mNormalArray;
    ref<ArrayAbstract> mColorArray;
    ref<ArrayAbstract> mSecondaryColorArray;
    ref<ArrayAbstract> mFogCoordArray;
    Collection<TextureArray> mTexCoordArrays;
    // generic vertex attributes
    Collection<VertexAttribInfo> mVertexAttribArrays;
  };
  //------------------------------------------------------------------------------
}

#endif