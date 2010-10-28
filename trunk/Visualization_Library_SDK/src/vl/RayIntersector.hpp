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

#ifndef RayIntersector_INCLUDE_ONCE
#define RayIntersector_INCLUDE_ONCE

#include <vl/Ray.hpp>
#include <vl/Actor.hpp>
#include <vl/Geometry.hpp>
#include <vl/Vector4.hpp>
#include <vl/Matrix4.hpp>
#include <vl/Frustum.hpp>

namespace vl
{
  class SceneManager;
  //-----------------------------------------------------------------------------
  // RayIntersection
  //-----------------------------------------------------------------------------
  /** The RayIntersection encapsulates all the information relative to a Ray/Actor intersection.
   */
  class RayIntersection: public Object
  {
  public:
    virtual const char* className() { return "RayIntersection"; }
    RayIntersection(): mActor(NULL), mDistance(0.0f) 
    {
      #ifndef NDEBUG
        mObjectName = className();
      #endif
    }

    //! The intersected Actor
    void setActor(Actor* a) { mActor = a; }
    //! The intersected Actor
    const Actor* actor() const { return mActor; }
    //! The intersected Actor
    Actor* actor() { return mActor; }

    //! The intersection point, in world coordinates
    const vec3& intersectionPoint() const { return mIntersectionPoint; }
    //! The intersection point, in world coordinates
    void setIntersectionPoint(const vec3& v) { mIntersectionPoint = v; }

    //! The intersection distance
    float distance() const { return mDistance; }
    //! The intersection distance
    void setDistance(float dist) { mDistance = dist; }

  protected:
    vec3 mIntersectionPoint;
    Actor* mActor;
    float mDistance;
  };
  //-----------------------------------------------------------------------------
  // RayIntersectionGeometry
  //-----------------------------------------------------------------------------
  /** The RayIntersectionGeometry encapsulates all the information relative to a Ray/Actor intersection, 
      providing also extra information relative to the intersection on the Geometry in use by the Actor.
   */
  class RayIntersectionGeometry: public RayIntersection
  {
  public:
    virtual const char* className() { return "RayIntersectionGeometry"; }
    RayIntersectionGeometry(): mGeometry(NULL), mDrawCalls(NULL), mPrimitiveIndex(-1) 
    {
      #ifndef NDEBUG
        mObjectName = className();
      #endif
    }

    //! The intersected Geometry
    Geometry* geometry() { return mGeometry; }
    //! The intersected Geometry
    const Geometry* geometry() const { return mGeometry; }
    //! The intersected DrawCall
    DrawCall* drawCalls() { return mDrawCalls; }
    //! The intersected DrawCall
    const DrawCall* drawCalls() const { return mDrawCalls; }
    //! The starting index of the intersected primitive inside drawCalls()
    int primitiveIndex() const { return mPrimitiveIndex; }

    //! The intersected Geometry
    void setGeometry(Geometry* g) { mGeometry = g; }
    //! The intersected DrawCall
    void setPrimitives(DrawCall* p) { mDrawCalls = p; }
    //! The starting index of the intersected primitive inside drawCalls()
    void setPrimitiveIndex(int p_idx) { mPrimitiveIndex = p_idx; }

  protected:
    vec3 mIntersectionPoint;
    Geometry* mGeometry;
    DrawCall* mDrawCalls;
    int mPrimitiveIndex;
    float mDistance;
  };
  //-----------------------------------------------------------------------------
  // RayIntersector
  //-----------------------------------------------------------------------------
  /** The RayIntersector class is used to detect the intersection points between a Ray and a set of Actor[s]
   */
  class RayIntersector: public Object
  {
  public:
    virtual const char* className() { return "RayIntersector"; }
    RayIntersector()
    {
      #ifndef NDEBUG
        mObjectName = className();
      #endif
      mActors = new ActorCollection;
    }

    //! The Actors against which the intersection test is performed.
    const ActorCollection* actors() const { return mActors.get(); }
    //! The Actors against which the intersection test is performed.
    ActorCollection* actors() { return mActors.get(); }

    //! The ray in world coordinates to be intersected with the actors()
    const Ray& ray() const { return mRay; }
    //! The ray in world coordinates to be intersected with the actors()
    void setRay(const Ray& ray) { mRay = ray; }

    //! The frustum in world coordinates used to cull the objects.
    const Frustum& frustum() const { return mFrustum; }
    //! The frustum in world coordinates used to cull the objects.
    void setFrustum(const Frustum& frustum) { mFrustum = frustum; }

    //! The intersection points detected by the last intersect() call sorted according to their distance (the first one is the closest).
    const std::vector< ref<RayIntersection> >& intersections() const { return mIntersections; }

    /** Executes the intersection test.
     * \note Before calling this function the transforms and the bounding volumes of the Actor[s] to be intersected must be updated, in this order.
     * \note All the intersections are mande on the Actor's LOD level #0.
     */
    void intersect();

    /** Computes the intersections between the given ray and the Actor[s] contained in the given scene manager.
      * This is an utility function equivalent to:
      * \code
      * intersector->actors()->clear();
      * scene_manager->extractActors( *intersector->actors() );
      * intersector->setRay(ray);
      * intersector->intersect();
      * \endcode
      */
    void intersect(const Ray& ray, SceneManager* scene_manager);

  protected:
    static bool sorter(const ref<RayIntersection>& a, const ref<RayIntersection>& b) { return a->distance() < b->distance(); }

    void intersect(Actor* act);
    void intersectGeometry(Actor* act, Geometry* geom);

    // T should be either fvec3-4 or dvec3-4
    template<class T>
    void intersectTriangle(const T& a, const T& b, const T& c, Actor*, Geometry* geom, DrawCall* prim, int prim_idx);

    // T should be either fvec3-4 or dvec3-4
    template<class T>
    void intersectPolygon(const std::vector<T>& polygon, Actor*, Geometry* geom, DrawCall* prim);

    // T should be either fvec3-4 or dvec3-4
    template<class T>
    void intersectQuad(const T& a, const T& b, const T& c, const T& d, Actor*, Geometry* geom, DrawCall* prim, int prim_idx);

  protected:
    Frustum mFrustum;
    std::vector< ref<RayIntersection> > mIntersections;
    ref<ActorCollection> mActors;
    Ray mRay;
  };
}

#endif
