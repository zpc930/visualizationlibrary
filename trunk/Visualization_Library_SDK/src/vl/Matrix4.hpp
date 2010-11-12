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

#ifndef Matrix4_INCLUDE_ONCE
#define Matrix4_INCLUDE_ONCE

#include <vl/Vector4.hpp>
#include <vl/Matrix3.hpp>

namespace vl
{
  //-----------------------------------------------------------------------------
  // Matrix4
  //-----------------------------------------------------------------------------
  /**
   * The Matrix4 class is a template class that implements a generic 4x4 matrix, see also vl::dmat4, vl::fmat4, vl::umat4, vl::imat4
   * \sa Vector4, Vector3, Vector2, Matrix3, Matrix2
   */
  template<typename T_scalar_type>
  class Matrix4
  {
  public:
    typedef T_scalar_type scalar_type;
    //-----------------------------------------------------------------------------
    template<typename T>
    explicit Matrix4(const T& m)
    {
      e(0,0) = (T_scalar_type)m.e(0,0); e(0,1) = (T_scalar_type)m.e(0,1); e(0,2) = (T_scalar_type)m.e(0,2); e(0,3) = (T_scalar_type)m.e(0,3);
      e(1,0) = (T_scalar_type)m.e(1,0); e(1,1) = (T_scalar_type)m.e(1,1); e(1,2) = (T_scalar_type)m.e(1,2); e(1,3) = (T_scalar_type)m.e(1,3);
      e(2,0) = (T_scalar_type)m.e(2,0); e(2,1) = (T_scalar_type)m.e(2,1); e(2,2) = (T_scalar_type)m.e(2,2); e(2,3) = (T_scalar_type)m.e(2,3);
      e(3,0) = (T_scalar_type)m.e(3,0); e(3,1) = (T_scalar_type)m.e(3,1); e(3,2) = (T_scalar_type)m.e(3,2); e(3,3) = (T_scalar_type)m.e(3,3);
    }
    //-----------------------------------------------------------------------------
    Matrix4()
    {
      static const T_scalar_type I4d[] = 
      {
        (T_scalar_type)1, (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)0, 
        (T_scalar_type)0, (T_scalar_type)1, (T_scalar_type)0, (T_scalar_type)0, 
        (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)1, (T_scalar_type)0, 
        (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)1 
      };
      memcpy( mVec, I4d, sizeof(T_scalar_type)*16 );
    }
    //-----------------------------------------------------------------------------
    Matrix4(T_scalar_type n)
    {
      static const T_scalar_type I4d[] = 
      {
        (T_scalar_type)1, (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)0, 
        (T_scalar_type)0, (T_scalar_type)1, (T_scalar_type)0, (T_scalar_type)0, 
        (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)1, (T_scalar_type)0, 
        (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)0, (T_scalar_type)1 
      };
      memcpy( mVec, I4d, sizeof(T_scalar_type)*16 );
      e(0,0) = n; e(1,1) = n; e(2,2) = n; e(3,3) = n; 
    }
    //-----------------------------------------------------------------------------
    explicit Matrix4( T_scalar_type e00, T_scalar_type e01, T_scalar_type e02, T_scalar_type e03,
                    T_scalar_type e10, T_scalar_type e11, T_scalar_type e12, T_scalar_type e13,
                    T_scalar_type e20, T_scalar_type e21, T_scalar_type e22, T_scalar_type e23,
                    T_scalar_type e30, T_scalar_type e31, T_scalar_type e32, T_scalar_type e33 )
    {
      e(0,0) = e00; e(0,1) = e01; e(0,2) = e02; e(0,3) = e03;
      e(1,0) = e10; e(1,1) = e11; e(1,2) = e12; e(1,3) = e13;
      e(2,0) = e20; e(2,1) = e21; e(2,2) = e22; e(2,3) = e23;
      e(3,0) = e30; e(3,1) = e31; e(3,2) = e32; e(3,3) = e33;
    }
    //-----------------------------------------------------------------------------
    Matrix4& fill(T_scalar_type val)
    {
      e(0,0) = e(0,1) = e(0,2) = e(0,3) = 
      e(1,0) = e(1,1) = e(1,2) = e(1,3) = 
      e(2,0) = e(2,1) = e(2,2) = e(2,3) = 
      e(3,0) = e(3,1) = e(3,2) = e(3,3) = val;
      return *this;
    }
    //-----------------------------------------------------------------------------
    T_scalar_type diff(const Matrix4& other)
    {
      T_scalar_type err = 0;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          if ( e(i,j) > other.e(i,j) ) // avoid fabs/abs
            err += e(i,j) - other.e(i,j);
          else
            err += other.e(i,j) - e(i,j);
      return err;
    }
    //-----------------------------------------------------------------------------
    const T_scalar_type& e(unsigned i, unsigned j) const { return (*this)[i][j]; }
    //-----------------------------------------------------------------------------
    T_scalar_type& e(unsigned i, unsigned j) { return (*this)[i][j]; }
    //-----------------------------------------------------------------------------
    const Vector4<T_scalar_type>& operator[](unsigned int i) const { VL_CHECK(i<4); return mVec[i]; }
    //-----------------------------------------------------------------------------
    Vector4<T_scalar_type>& operator[](unsigned int i) { VL_CHECK(i<4); return mVec[i]; }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar_type> getX() const
    {
      return Vector3<T_scalar_type>(mVec[0].x(), mVec[0].y(), mVec[0].z());
    }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar_type> getY() const
    {
      return Vector3<T_scalar_type>(mVec[1].x(), mVec[1].y(), mVec[1].z());
    }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar_type> getZ() const
    {
      return Vector3<T_scalar_type>(mVec[2].x(), mVec[2].y(), mVec[2].z());
    }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar_type> getT() const
    {
      return Vector3<T_scalar_type>(mVec[3].x(), mVec[3].y(), mVec[3].z());
    }
    //-----------------------------------------------------------------------------
    Matrix4& setX(const Vector3<T_scalar_type>& v) 
    {
      mVec[0].x() = v.x();
      mVec[0].y() = v.y();
      mVec[0].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& setY(const Vector3<T_scalar_type>& v) 
    {
      mVec[1].x() = v.x();
      mVec[1].y() = v.y();
      mVec[1].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& setZ(const Vector3<T_scalar_type>& v) 
    {
      mVec[2].x() = v.x();
      mVec[2].y() = v.y();
      mVec[2].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& setT(const Vector3<T_scalar_type>& v) 
    {
      mVec[3].x() = v.x();
      mVec[3].y() = v.y();
      mVec[3].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    bool operator==(const Matrix4& m) const
    {
      return memcmp(m.mVec, mVec, sizeof(T_scalar_type)*4*4) == 0;
    }
    //-----------------------------------------------------------------------------
    bool operator!=(const Matrix4& m) const
    {
      return !(*this == m);
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator=(const Matrix4& m)
    {
      memcpy(mVec, m.mVec, sizeof(T_scalar_type)*16);
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator+(const Matrix4& m) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t[i][j] = e(i,j) + m[i][j];

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator+=(const Matrix4& m)
    {
      return *this = *this + m;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator-(const Matrix4& m) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t[i][j] = e(i,j) - m[i][j];

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator-=(const Matrix4& m)
    {
      return *this = *this - m;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator*=(const Matrix4& m)
    {
      return *this = *this * m;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator-() const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t[i][j] = -e(i,j);

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator+(T_scalar_type d) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t[i][j] = e(i,j) + d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator+=(T_scalar_type d)
    {
      return *this = *this + d;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator-(T_scalar_type d) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t[i][j] = e(i,j) - d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator-=(T_scalar_type d)
    {
      return *this = *this - d;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator*(T_scalar_type d) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t[i][j] = e(i,j) * d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator*=(T_scalar_type d)
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(i,j) *= d;

      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator/(T_scalar_type d) const
    {
      d = (T_scalar_type)1 / d;
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t[i][j] = e(i,j) * d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator/=(T_scalar_type d)
    {
      d = (T_scalar_type)1 / d;
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(i,j) *= d;

      return *this;
    }
    //-----------------------------------------------------------------------------
    bool isIdentity() const
    {
      Matrix4 i;
      return memcmp( ptr(), i.ptr(), sizeof(T_scalar_type)*16 ) == 0;
    }
    //-----------------------------------------------------------------------------
    Matrix4 as3x3() const
    {
      Matrix4 t = *this;
      t[0][3] = 0;
      t[1][3] = 0;
      t[2][3] = 0;
      t[3][3] = 1;
      t[3][0] = 0;
      t[3][1] = 0;
      t[3][2] = 0;
      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3<T_scalar_type> get3x3() const
    {
      Matrix3<T_scalar_type> t;
      t.e(0,0) = e(0,0); t.e(0,1) = e(0,1); t.e(0,2) = e(0,2);
      t.e(1,0) = e(1,0); t.e(1,1) = e(1,1); t.e(1,2) = e(1,2);
      t.e(2,0) = e(2,0); t.e(2,1) = e(2,1); t.e(2,2) = e(2,2);
      return t;
    }
    //-----------------------------------------------------------------------------
    //! This writes only on the upper 3x3 part of the matrix without touching the last row and column. 
    void set3x3(const Matrix3<T_scalar_type>& m)
    {
      e(0,0) = m.e(0,0); e(0,1) = m.e(0,1); e(0,2) = m.e(0,2);
      e(1,0) = m.e(1,0); e(1,1) = m.e(1,1); e(1,2) = m.e(1,2);
      e(2,0) = m.e(2,0); e(2,1) = m.e(2,1); e(2,2) = m.e(2,2);
    }
    //-----------------------------------------------------------------------------
    T_scalar_type* ptr()
    {
      return &e(0,0);
    }
    //-----------------------------------------------------------------------------
    const T_scalar_type* ptr() const
    {
      return &e(0,0);
    }
    //-----------------------------------------------------------------------------
    Matrix4& transpose()
    {
      Matrix4 m;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          m.e(i,j) = e(j,i);
      memcpy(mVec, m.mVec, sizeof(T_scalar_type)*16);
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 getTransposed() const
    {
      Matrix4 m;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          m.e(i,j) = e(j,i);
      return m;
    }
    //-----------------------------------------------------------------------------
    void getTransposed(Matrix4& dest) const
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          dest.e(i,j) = e(j,i);
    }
    //-----------------------------------------------------------------------------
    bool isNull() const
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          if( e(j,i) != 0 )
            return false;
      return true;
    }
    //-----------------------------------------------------------------------------
    void setIdentity()
    {
      *this = Matrix4();
    }
    //-----------------------------------------------------------------------------
    T_scalar_type getInverse(Matrix4& dest) const;
    //-----------------------------------------------------------------------------
    Matrix4 getInverse(T_scalar_type *determinant=NULL) const
    {
      Matrix4 tmp;
      T_scalar_type det = getInverse(tmp);
      if (determinant)
        *determinant = det;
      return tmp;
    }
    //-----------------------------------------------------------------------------
    Matrix4& invert(T_scalar_type *determinant=NULL)
    {
      T_scalar_type det = getInverse(*this);
      if (determinant )
        *determinant = det;
      return *this;
    }
    //-----------------------------------------------------------------------------
    const T_scalar_type& e(int i, int j) const { return mVec[i][j]; }
    //-----------------------------------------------------------------------------
    T_scalar_type& e(int i, int j) { return mVec[i][j]; }
    //-----------------------------------------------------------------------------
    static Matrix4 perspective(T_scalar_type fovy, T_scalar_type aspect_ratio, T_scalar_type znear, T_scalar_type zfar);
    //-----------------------------------------------------------------------------
    static Matrix4 frustum( T_scalar_type pleft, T_scalar_type pright, T_scalar_type pbottom, T_scalar_type ptop, T_scalar_type pnear, T_scalar_type pfar);
    //-----------------------------------------------------------------------------
    static Matrix4 ortho(T_scalar_type pleft, T_scalar_type pright, T_scalar_type pbottom, T_scalar_type ptop, T_scalar_type pnear, T_scalar_type pfar);
    //-----------------------------------------------------------------------------
    static Matrix4 ortho2D(T_scalar_type pleft, T_scalar_type pright, T_scalar_type pbottom, T_scalar_type ptop);
    //-----------------------------------------------------------------------------
    static Matrix4 lookAt( const Vector3<T_scalar_type>& eye, const Vector3<T_scalar_type>& look, const Vector3<T_scalar_type>& up);
    //-----------------------------------------------------------------------------
    void getAsLookAt( Vector3<T_scalar_type>& eye, Vector3<T_scalar_type>& look, Vector3<T_scalar_type>& up, Vector3<T_scalar_type>& right) const;
    //-----------------------------------------------------------------------------
    static Matrix4 rotation( T_scalar_type degrees, T_scalar_type x, T_scalar_type y, T_scalar_type z );
    //-----------------------------------------------------------------------------
    static Matrix4 rotation( T_scalar_type degrees, const Vector3<T_scalar_type>& v )
    {
      return rotation( degrees, v.x(), v.y(), v.z() );
    }
    //-----------------------------------------------------------------------------
    static Matrix4 rotation( T_scalar_type degrees1, const Vector3<T_scalar_type>& v1, T_scalar_type degrees2, const Vector3<T_scalar_type>& v2 )
    {
      return rotation( degrees1, v1.x(), v1.y(), v1.z() ) * rotation( degrees2, v2.x(), v2.y(), v2.z() );
    }
    //-----------------------------------------------------------------------------
    static Matrix4 rotation( T_scalar_type degrees1, const Vector3<T_scalar_type>& v1, T_scalar_type degrees2, const Vector3<T_scalar_type>& v2, T_scalar_type degrees3, const Vector3<T_scalar_type>& v3 )
    {
      return rotation( degrees1, v1.x(), v1.y(), v1.z() ) * rotation( degrees2, v2.x(), v2.y(), v2.z() ) * rotation( degrees3, v3.x(), v3.y(), v3.z() );
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate( T_scalar_type degrees, const Vector3<T_scalar_type>& v )
    {
      return rotate( degrees, v.x(), v.y(), v.z() );
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate( T_scalar_type degrees, T_scalar_type x, T_scalar_type y, T_scalar_type z )
    {
      *this = rotation(degrees, x, y, z) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate( T_scalar_type degrees1, const Vector3<T_scalar_type>& v1, T_scalar_type degrees2, const Vector3<T_scalar_type>& v2 )
    {
      *this = rotation(degrees1, v1, degrees2, v2) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    void getYXRotationAngles( T_scalar_type& degrees_y, T_scalar_type& degrees_x ) const;
    //-----------------------------------------------------------------------------
    Matrix4& rotate( T_scalar_type degrees1, const Vector3<T_scalar_type>& v1, T_scalar_type degrees2, const Vector3<T_scalar_type>& v2, T_scalar_type degrees3, const Vector3<T_scalar_type>& v3 )
    {
      *this = rotation(degrees1, v1, degrees2, v2, degrees3, v3) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 rotationXYZ( T_scalar_type degX, T_scalar_type degY, T_scalar_type degZ)
    {
      return rotation(degX, 1,0,0) * rotation(degY, 0,1,0) * rotation(degZ, 0,0,1);
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotateXYZ( T_scalar_type degX, T_scalar_type degY, T_scalar_type degZ )
    {
      *this = rotationXYZ(degX, degY, degZ) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 rotationZYX( T_scalar_type degZ, T_scalar_type degY, T_scalar_type degX)
    {
      return rotation(degZ, 0,0,1) * rotation(degY, 0,1,0) * rotation(degX, 1,0,0);
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotateZYX( T_scalar_type degZ, T_scalar_type degY, T_scalar_type degX )
    {
      *this = rotationZYX(degZ, degY, degX) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 rotation(const Vector4<T_scalar_type>& from, const Vector4<T_scalar_type>& to)
    {
      return rotation( from.xyz(), to.xyz() );
    }
    //-----------------------------------------------------------------------------
    static Matrix4 rotation(const Vector3<T_scalar_type>& from, const Vector3<T_scalar_type>& to);
    //-----------------------------------------------------------------------------
    Matrix4& rotate(const Vector4<T_scalar_type>& from, const Vector4<T_scalar_type>& to)
    {
      *this = rotation(from, to) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate(const Vector3<T_scalar_type>& from, const Vector3<T_scalar_type>& to)
    {
      *this = rotation(from, to) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 translation( const Vector3<T_scalar_type>& v )
    {
      return translation(v.x(), v.y(), v.z());
    }
    //-----------------------------------------------------------------------------
    static Matrix4 translation( T_scalar_type x, T_scalar_type y, T_scalar_type z )
    {
      Matrix4 tr;
      tr.e(3,0) = x;
      tr.e(3,1) = y;
      tr.e(3,2) = z;
      return tr;
    }
    //-----------------------------------------------------------------------------
    Matrix4& translate( T_scalar_type x, T_scalar_type y, T_scalar_type z )
    {
      *this = translation(x,y,z) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& translate( const Vector3<T_scalar_type>& v )
    {
      *this = translation(v) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 scaling( const Vector3<T_scalar_type>& v )
    {
      return scaling( v.x(), v.y(), v.z() );
    }
    //-----------------------------------------------------------------------------
    static Matrix4 scaling( T_scalar_type x, T_scalar_type y, T_scalar_type z )
    {
      Matrix4 sc;
      sc.e(0,0) = x;
      sc.e(1,1) = y;
      sc.e(2,2) = z;
      return sc;
    }
    //-----------------------------------------------------------------------------
    Matrix4& scale( T_scalar_type x, T_scalar_type y, T_scalar_type z )
    {
      *this = scaling(x,y,z) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------

  protected:
    Vector4<T_scalar_type> mVec[4];
  };
  //-----------------------------------------------------------------------------
  // OPERATORS
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  inline Matrix4<T_scalar_type> operator*(const Matrix4<T_scalar_type>& m2, const Matrix4<T_scalar_type>& m1)
  {
    Matrix4<T_scalar_type> t;
    t.e(0,0) = m1.e(0,0)*m2.e(0,0) + m1.e(0,1)*m2.e(1,0) + m1.e(0,2)*m2.e(2,0) + m1.e(0,3)*m2.e(3,0);
    t.e(1,0) = m1.e(1,0)*m2.e(0,0) + m1.e(1,1)*m2.e(1,0) + m1.e(1,2)*m2.e(2,0) + m1.e(1,3)*m2.e(3,0);
    t.e(2,0) = m1.e(2,0)*m2.e(0,0) + m1.e(2,1)*m2.e(1,0) + m1.e(2,2)*m2.e(2,0) + m1.e(2,3)*m2.e(3,0);
    t.e(3,0) = m1.e(3,0)*m2.e(0,0) + m1.e(3,1)*m2.e(1,0) + m1.e(3,2)*m2.e(2,0) + m1.e(3,3)*m2.e(3,0);

    t.e(0,1) = m1.e(0,0)*m2.e(0,1) + m1.e(0,1)*m2.e(1,1) + m1.e(0,2)*m2.e(2,1) + m1.e(0,3)*m2.e(3,1);
    t.e(1,1) = m1.e(1,0)*m2.e(0,1) + m1.e(1,1)*m2.e(1,1) + m1.e(1,2)*m2.e(2,1) + m1.e(1,3)*m2.e(3,1);
    t.e(2,1) = m1.e(2,0)*m2.e(0,1) + m1.e(2,1)*m2.e(1,1) + m1.e(2,2)*m2.e(2,1) + m1.e(2,3)*m2.e(3,1);
    t.e(3,1) = m1.e(3,0)*m2.e(0,1) + m1.e(3,1)*m2.e(1,1) + m1.e(3,2)*m2.e(2,1) + m1.e(3,3)*m2.e(3,1);

    t.e(0,2) = m1.e(0,0)*m2.e(0,2) + m1.e(0,1)*m2.e(1,2) + m1.e(0,2)*m2.e(2,2) + m1.e(0,3)*m2.e(3,2);
    t.e(1,2) = m1.e(1,0)*m2.e(0,2) + m1.e(1,1)*m2.e(1,2) + m1.e(1,2)*m2.e(2,2) + m1.e(1,3)*m2.e(3,2);
    t.e(2,2) = m1.e(2,0)*m2.e(0,2) + m1.e(2,1)*m2.e(1,2) + m1.e(2,2)*m2.e(2,2) + m1.e(2,3)*m2.e(3,2);
    t.e(3,2) = m1.e(3,0)*m2.e(0,2) + m1.e(3,1)*m2.e(1,2) + m1.e(3,2)*m2.e(2,2) + m1.e(3,3)*m2.e(3,2);

    t.e(0,3) = m1.e(0,0)*m2.e(0,3) + m1.e(0,1)*m2.e(1,3) + m1.e(0,2)*m2.e(2,3) + m1.e(0,3)*m2.e(3,3);
    t.e(1,3) = m1.e(1,0)*m2.e(0,3) + m1.e(1,1)*m2.e(1,3) + m1.e(1,2)*m2.e(2,3) + m1.e(1,3)*m2.e(3,3);
    t.e(2,3) = m1.e(2,0)*m2.e(0,3) + m1.e(2,1)*m2.e(1,3) + m1.e(2,2)*m2.e(2,3) + m1.e(2,3)*m2.e(3,3);
    t.e(3,3) = m1.e(3,0)*m2.e(0,3) + m1.e(3,1)*m2.e(1,3) + m1.e(3,2)*m2.e(2,3) + m1.e(3,3)*m2.e(3,3);
    return t;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  inline Matrix4<T_scalar_type> operator+(T_scalar_type d, const Matrix4<T_scalar_type>& m)
  {
    return m + d;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  inline Matrix4<T_scalar_type> operator*(T_scalar_type d, const Matrix4<T_scalar_type>& m)
  {
    return m * d;
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  template<typename T_scalar_type>
  inline Vector4<T_scalar_type> operator*(const Matrix4<T_scalar_type>& m, const Vector4<T_scalar_type>& v)
  {
    return Vector4<T_scalar_type>(
      v.x()*m.e(0,0) + v.y()*m.e(1,0) + v.z()*m.e(2,0) + v.w()*m.e(3,0),
      v.x()*m.e(0,1) + v.y()*m.e(1,1) + v.z()*m.e(2,1) + v.w()*m.e(3,1),
      v.x()*m.e(0,2) + v.y()*m.e(1,2) + v.z()*m.e(2,2) + v.w()*m.e(3,2),
      v.x()*m.e(0,3) + v.y()*m.e(1,3) + v.z()*m.e(2,3) + v.w()*m.e(3,3)
    );
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  //! The incoming vector is considered a Vector4<T_scalar_type> with the component w = 1
  template<typename T_scalar_type>
  inline Vector3<T_scalar_type> operator*(const Matrix4<T_scalar_type>& m, const Vector3<T_scalar_type>& v)
  {
    return Vector3<T_scalar_type>(
      v.x()*m.e(0,0) + v.y()*m.e(1,0) + v.z()*m.e(2,0) + /*1**/m.e(3,0),
      v.x()*m.e(0,1) + v.y()*m.e(1,1) + v.z()*m.e(2,1) + /*1**/m.e(3,1),
      v.x()*m.e(0,2) + v.y()*m.e(1,2) + v.z()*m.e(2,2) + /*1**/m.e(3,2)
    );
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  //! The incoming vector is considered a Vector4<T_scalar_type> with components: z = 0 and w = 1
  template<typename T_scalar_type>
  inline Vector2<T_scalar_type> operator*(const Matrix4<T_scalar_type>& m, const Vector2<T_scalar_type>& v)
  {
    return Vector2<T_scalar_type>(
      v.x()*m.e(0,0) + v.y()*m.e(1,0) + /*0*m.e(2,0) +*/ /*1**/m.e(3,0),
      v.x()*m.e(0,1) + v.y()*m.e(1,1) + /*0*m.e(2,1) +*/ /*1**/m.e(3,1)
    );
  }
  //-----------------------------------------------------------------------------
  //! Pre multiplication: row vector * matrix
  template<typename T_scalar_type>
  inline Vector4<T_scalar_type> operator*(const Vector4<T_scalar_type>& v, const Matrix4<T_scalar_type>& m)
  {
    return Vector4<T_scalar_type>(
      v.x()*m.e(0,0) + v.y()*m.e(0,1) + v.z()*m.e(0,2) + v.w()*m.e(0,3),
      v.x()*m.e(1,0) + v.y()*m.e(1,1) + v.z()*m.e(1,2) + v.w()*m.e(1,3),
      v.x()*m.e(2,0) + v.y()*m.e(2,1) + v.z()*m.e(2,2) + v.w()*m.e(2,3),
      v.x()*m.e(3,0) + v.y()*m.e(3,1) + v.z()*m.e(3,2) + v.w()*m.e(3,3)
    );
  }
  //-----------------------------------------------------------------------------
  //! Pre multiplication: row vector * matrix
  //! The incoming vector is considered a Vector4<T_scalar_type> with the component w = 1
  template<typename T_scalar_type>
  inline Vector3<T_scalar_type> operator*(const Vector3<T_scalar_type>& v, const Matrix4<T_scalar_type>& m)
  {
    return Vector3<T_scalar_type>(
      v.x()*m.e(0,0) + v.y()*m.e(0,0) + v.z()*m.e(0,0) + /*1**/m.e(0,0),
      v.x()*m.e(1,0) + v.y()*m.e(1,0) + v.z()*m.e(1,0) + /*1**/m.e(1,0),
      v.x()*m.e(2,0) + v.y()*m.e(2,0) + v.z()*m.e(2,0) + /*1**/m.e(2,0)
    );
  }
  //-----------------------------------------------------------------------------
  //! Pre multiplication: row vector * matrix
  //! The incoming vector is considered a Vector4<T_scalar_type> with components: z = 0 and w = 1
  template<typename T_scalar_type>
  inline Vector2<T_scalar_type> operator*(const Vector2<T_scalar_type>& v, const Matrix4<T_scalar_type>& m)
  {
    return Vector2<T_scalar_type>(
      v.x()*m.e(0,0) + v.y()*m.e(0,1) + /*0*m.e(2,0) +*/ /*1**/m.e(0,3),
      v.x()*m.e(1,0) + v.y()*m.e(1,1) + /*0*m.e(2,1) +*/ /*1**/m.e(1,3)
    );
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  Matrix4<T_scalar_type> Matrix4<T_scalar_type>::lookAt( const Vector3<T_scalar_type>& eye, const Vector3<T_scalar_type>& look, const Vector3<T_scalar_type>& up)
  {
    Vector3<T_scalar_type> y = Vector3<T_scalar_type>(up).normalize();
    Vector3<T_scalar_type> z = (eye - look).normalize(); // == -(look-eye)
    Vector3<T_scalar_type> x = cross(y,z).normalize();
    y = cross(z, x).normalize();
    
    Matrix4<T_scalar_type> m;

    m.setT(eye);
    m.setX(x);
    m.setY(y);
    m.setZ(z);

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  void Matrix4<T_scalar_type>::getAsLookAt( Vector3<T_scalar_type>& eye, Vector3<T_scalar_type>& look, Vector3<T_scalar_type>& up, Vector3<T_scalar_type>& right) const
  {
    eye = getT();

    look = -getZ();
    look.normalize();

    up = getY();
    up.normalize();

    right = getX();
    right.normalize();
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  Matrix4<T_scalar_type> Matrix4<T_scalar_type>::perspective(T_scalar_type fovy, T_scalar_type aspect_ratio, T_scalar_type znear, T_scalar_type zfar)
  {
    Matrix4<T_scalar_type> m;

    T_scalar_type rads = (fovy / ((T_scalar_type)2)) * (T_scalar_type)dDEG_TO_RAD;
    T_scalar_type dz = zfar - znear;
    T_scalar_type sa = sin(rads);
    if ((dz == 0) || (sa == 0) || (aspect_ratio == 0)) 
      return m * 0;
    T_scalar_type ctan = cos(rads) / sa;

    m.e(0,0) = (T_scalar_type)(ctan / aspect_ratio);
    m.e(1,1) = (T_scalar_type)(ctan);
    m.e(2,2) = (T_scalar_type)(-(zfar + znear) / dz);
    m.e(2,3) = -((T_scalar_type)1);
    m.e(3,2) = (T_scalar_type)(-((T_scalar_type)2) * znear * zfar / dz);
    m.e(3,3) = 0;

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  Matrix4<T_scalar_type> Matrix4<T_scalar_type>::frustum( T_scalar_type left, T_scalar_type right, T_scalar_type bottom, T_scalar_type top, T_scalar_type pnear, T_scalar_type pfar)
  {
    Matrix4<T_scalar_type> m;

    if (pnear <= 0 || pfar <= 0 || pnear == pfar || left == right || top == bottom)
      return m * 0;

    T_scalar_type x =  (((T_scalar_type)2)*pnear)  / (right-left);
    T_scalar_type y =  (((T_scalar_type)2)*pnear)  / (top-bottom);
    T_scalar_type a =  (right+left) / (right-left);
    T_scalar_type b =  (top+bottom) / (top-bottom);
    T_scalar_type c = -(pfar+pnear)   / ( pfar-pnear);
    T_scalar_type d = -(((T_scalar_type)2)*pfar*pnear) / (pfar-pnear);

    m.e(0,0) = x;  m.e(1,0) = 0;  m.e(2,0) = a;    m.e(3,0) = 0;
    m.e(0,1) = 0;  m.e(1,1) = y;  m.e(2,1) = b;    m.e(3,1) = 0;
    m.e(0,2) = 0;  m.e(1,2) = 0;  m.e(2,2) = c;    m.e(3,2) = d;
    m.e(0,3) = 0;  m.e(1,3) = 0;  m.e(2,3) = -((T_scalar_type)1); m.e(3,3) = 0;

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  Matrix4<T_scalar_type> Matrix4<T_scalar_type>::ortho(T_scalar_type left, T_scalar_type right, T_scalar_type bottom, T_scalar_type top, T_scalar_type pnear, T_scalar_type pfar)
  {
    Matrix4<T_scalar_type> m;

    m.e(0,0) = ((T_scalar_type)2) / (right-left);
    m.e(1,0) = 0;
    m.e(2,0) = 0;
    m.e(3,0) = -(right+left) / (right-left);

    m.e(0,1) = 0;
    m.e(1,1) = ((T_scalar_type)2) / (top-bottom);
    m.e(2,1) = 0;
    m.e(3,1) = -(top+bottom) / (top-bottom);

    m.e(0,2) = 0;
    m.e(1,2) = 0;
    m.e(2,2) = -((T_scalar_type)2) / (pfar-pnear);
    m.e(3,2) = -(pfar+pnear) / (pfar-pnear);

    m.e(0,3) = 0;
    m.e(1,3) = 0;
    m.e(2,3) = 0;
    m.e(3,3) = ((T_scalar_type)1);

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  Matrix4<T_scalar_type> Matrix4<T_scalar_type>::ortho2D(T_scalar_type left, T_scalar_type right, T_scalar_type bottom, T_scalar_type top)
  {
    return ortho(left, right, bottom, top, -1, +1);
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  Matrix4<T_scalar_type> Matrix4<T_scalar_type>::rotation( T_scalar_type degrees, T_scalar_type x, T_scalar_type y, T_scalar_type z )
  {
    Matrix4<T_scalar_type> rot;

    if ( degrees == 0 || (x == 0 && y ==0 && z == 0) )
      return rot;
      
    degrees = T_scalar_type(degrees * dDEG_TO_RAD);

    T_scalar_type xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;

    s = (T_scalar_type) sin( degrees );
    c = (T_scalar_type) cos( degrees );

    // simple cases
    if (x == 0) 
    {
      if (y == 0) 
      {
        if (z != 0) 
        {
          // rotate only around z-axis
          rot.e(0,0) = (T_scalar_type)c;
          rot.e(1,1) = (T_scalar_type)c;
          if (z < 0) 
          {
            rot.e(0,1) = -(T_scalar_type)s;
            rot.e(1,0) = (T_scalar_type)s;
          }
          else 
          {
            rot.e(0,1) = (T_scalar_type)s;
            rot.e(1,0) = -(T_scalar_type)s;
          }
          return rot;
        }
      }
      else if (z == 0) 
      {
        // rotate only around y-axis
        rot.e(0,0) = (T_scalar_type)c;
        rot.e(2,2) = (T_scalar_type)c;
        if (y < 0) 
        {
          rot.e(0,2) = (T_scalar_type)s;
          rot.e(2,0) = -(T_scalar_type)s;
        }
        else 
        {
          rot.e(0,2) = -(T_scalar_type)s;
          rot.e(2,0) = (T_scalar_type)s;
        }
        return rot;
      }
    }
    else if (y == 0) 
    {
      if (z == 0) 
      {
        // rotate only around x-axis
        rot.e(1,1) = (T_scalar_type)c;
        rot.e(2,2) = (T_scalar_type)c;
        if (x < 0) 
        {
          rot.e(1,2) = -(T_scalar_type)s;
          rot.e(2,1) = (T_scalar_type)s;
        }
        else 
        {
          rot.e(1,2) = (T_scalar_type)s;
          rot.e(2,1) = -(T_scalar_type)s;
        }
        return rot;
      }
    }

    // Beginning of general axisa to matrix conversion
    T_scalar_type dot = x*x + y*y + z*z;

    if (dot > (T_scalar_type)((T_scalar_type)1.0001) || dot < (T_scalar_type)0.99999) 
    {
      T_scalar_type mag = (T_scalar_type) sqrt(dot);
      x /= mag;
      y /= mag;
      z /= mag;
    }

    xx = x *x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = ((T_scalar_type)1) - c;

    rot.e(0,0) = (T_scalar_type)((one_c * xx) + c ); rot.e(0,1) = (T_scalar_type)((one_c * xy) + zs); rot.e(0,2) = (T_scalar_type)((one_c * zx) - ys);
    rot.e(1,0) = (T_scalar_type)((one_c * xy) - zs); rot.e(1,1) = (T_scalar_type)((one_c * yy) + c ); rot.e(1,2) = (T_scalar_type)((one_c * yz) + xs);
    rot.e(2,0) = (T_scalar_type)((one_c * zx) + ys); rot.e(2,1) = (T_scalar_type)((one_c * yz) - xs); rot.e(2,2) = (T_scalar_type)((one_c * zz) + c );
    return rot;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  T_scalar_type Matrix4<T_scalar_type>::getInverse(Matrix4<T_scalar_type>& dest) const
  {
    if (&dest == this)
    {
      Matrix4<T_scalar_type> tmp;
      T_scalar_type det = getInverse(tmp);
      dest = tmp;
      return det;
    }
    else
    {
      int i,j,k;
      int pvt_i[4], pvt_j[4];
      T_scalar_type pvt_val;
      T_scalar_type tmp;
      T_scalar_type det;

      dest = *this; // memcpy(dest, mVec, sizeof(T_scalar_type)*16);

      det = ((T_scalar_type)1);
      for (k=0; k<4; k++)
      {
        pvt_val=dest[k][k];
        pvt_i[k]=k;
        pvt_j[k]=k;
        for (i=k; i<4; ++i)
        {
          for (j=k; j<4; ++j)
          {
            if (fabs(dest[i][j]) > fabs(pvt_val))
            {
              pvt_i[k]=i;
              pvt_j[k]=j;
              pvt_val=dest[i][j];
            }
          }
        }

        det*=pvt_val;
        if (det == 0) 
        {
          dest.fill(0);
          return det;
        }

        i=pvt_i[k];
        if (i!=k) 
        {
          for (j=0; j<4; ++j) 
          {
            tmp=-dest[k][j];
            dest[k][j]=dest[i][j];
            dest[i][j]=tmp;
          }
        }

        j=pvt_j[k];
        if (j!=k) 
        {
          for (i=0; i<4; ++i) 
          {
            tmp=-dest[i][k];
            dest[i][k]=dest[i][j];
            dest[i][j]=tmp;
          }
        }

        for (i=0; i<4; ++i) {
          if (i!=k) dest[i][k]/=( -pvt_val);
        }

        for (i=0; i<4; ++i) 
        {
          tmp = dest[i][k];
          for (j=0; j<4; ++j) 
          {
            if (i!=k && j!=k) dest[i][j]+=tmp*dest[k][j];
          }
        }

        for (j=0; j<4; ++j) 
        {
          if (j!=k) dest[k][j]/=pvt_val;
        }

        dest[k][k] = ((T_scalar_type)1)/pvt_val;
      }

      for (k=4-2; k>=0; k--) 
      {
        i=pvt_j[k];
        if (i!=k) 
        {
          for(j=0; j<4; ++j) 
          {
            tmp = dest[k][j];
            dest[k][j]=-dest[i][j];
            dest[i][j]=tmp;
          }
        }

        j=pvt_i[k];
        if (j!=k)
        for (i=0; i<4; ++i) 
        {
          tmp=dest[i][k];
          dest[i][k]=-dest[i][j];
          dest[i][j]=tmp;
        }
      }

      return det;
    }
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar_type>
  Matrix4<T_scalar_type> Matrix4<T_scalar_type>::rotation(const Vector3<T_scalar_type>& from, const Vector3<T_scalar_type>& to)
  {
    Vector3<T_scalar_type> a,b;
    a = from;
    b = to;
    a.normalize();
    b.normalize();
    T_scalar_type cosa = dot(a,b);
    cosa = clamp(cosa,-((T_scalar_type)1),+((T_scalar_type)1));
    Vector3<T_scalar_type> axis,n2;
    axis = cross(a,b);
    axis.normalize();
    T_scalar_type alpha = acos( cosa );
    return rotation(alpha*(T_scalar_type)dRAD_TO_DEG, axis.x(), axis.y(), axis.z());
  }
  //-----------------------------------------------------------------------------
  //! If this matrix can be represented as \p RY(degrees_y) * \p RX(degrees_x), where 
  //! RX and RY are rotation matrices around the X and Y axis respectively, this 
  //! function returns the rotation angles \p degrees_y and \p degrees_x.
  //! \note This function can only retrieve angles that satisfy the following conditions:
  //! - -180 <= degrees_y <= 180
  //! - -180 <= degrees_x <= 180 and degrees_x != 90
  template<typename T_scalar_type>
  void Matrix4<T_scalar_type>::getYXRotationAngles( T_scalar_type& degrees_y, T_scalar_type& degrees_x ) const
  {
    Vector3<T_scalar_type> vx = getX();
    Vector3<T_scalar_type> vy = getY();
    Vector3<T_scalar_type> vz = getZ();

    vx.normalize();
    vy.normalize();
    vz.normalize();

    T_scalar_type kx = dot(vy,Vector3<T_scalar_type>(0,1,0));
    kx = clamp(kx,-((T_scalar_type)1),+((T_scalar_type)1));
    degrees_x = acos( kx ) * (T_scalar_type)dRAD_TO_DEG;
    if( dot(vz, Vector3<T_scalar_type>(0,1,0)) > 0 )
      degrees_x = -degrees_x;

    T_scalar_type ky = dot(vx, Vector3<T_scalar_type>(1,0,0));
    ky = clamp(ky,-((T_scalar_type)1),+((T_scalar_type)1));
    degrees_y = acos( ky ) * (T_scalar_type)dRAD_TO_DEG;
    if( dot(vz, Vector3<T_scalar_type>(1,0,0)) < 0 )
      degrees_y = -degrees_y;
    if (fabs(degrees_x) > (T_scalar_type)90)
      degrees_y = -degrees_y;
  }
  //-----------------------------------------------------------------------------

  //! A 4x4 matrix using \p GLdouble precision.
  typedef Matrix4<GLdouble> dmat4;
  //! A 4x4 matrix using \p GLfloat precision.
  typedef Matrix4<GLfloat>  fmat4;
  //! A 4x4 matrix using \p GLint precision.
  typedef Matrix4<GLint>    imat4;
  //! A 4x4 matrix using \p GLuint precision.
  typedef Matrix4<GLuint>  umat4;

  #if VL_PIPELINE_PRECISION == 2
    //! Defined as: \p 'typedef \p dmat4 \p mat4'. See also \ref VL_PIPELINE_PRECISION.
    typedef dmat4 mat4;
  #else
    //! Defined as: \p 'typedef \p fmat4 \p mat4'. See also \ref VL_PIPELINE_PRECISION.
    typedef fmat4 mat4;
  #endif
}

#endif
