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
  template<typename T_scalar>
  class Matrix4
  {
  public:
    typedef T_scalar scalar_type;
    //-----------------------------------------------------------------------------
    template<typename T>
    explicit Matrix4(const Matrix4<T>& m)
    {
      e(0,0) = (T_scalar)m.e(0,0); e(1,0) = (T_scalar)m.e(1,0); e(2,0) = (T_scalar)m.e(2,0); e(3,0) = (T_scalar)m.e(3,0);
      e(0,1) = (T_scalar)m.e(0,1); e(1,1) = (T_scalar)m.e(1,1); e(2,1) = (T_scalar)m.e(2,1); e(3,1) = (T_scalar)m.e(3,1);
      e(0,2) = (T_scalar)m.e(0,2); e(1,2) = (T_scalar)m.e(1,2); e(2,2) = (T_scalar)m.e(2,2); e(3,2) = (T_scalar)m.e(3,2);
      e(0,3) = (T_scalar)m.e(0,3); e(1,3) = (T_scalar)m.e(1,3); e(2,3) = (T_scalar)m.e(2,3); e(3,3) = (T_scalar)m.e(3,3);
    }
    //-----------------------------------------------------------------------------
    Matrix4()
    {
      setIdentity();
    }
    //-----------------------------------------------------------------------------
    explicit Matrix4(T_scalar n)
    {
      setIdentity();
      e(0,0) = e(1,1) = e(2,2) = e(3,3) = n; 
    }
    //-----------------------------------------------------------------------------
    explicit Matrix4(T_scalar e00, T_scalar e01, T_scalar e02, T_scalar e03,
                      T_scalar e10, T_scalar e11, T_scalar e12, T_scalar e13,
                      T_scalar e20, T_scalar e21, T_scalar e22, T_scalar e23,
                      T_scalar e30, T_scalar e31, T_scalar e32, T_scalar e33)
    {
      e(0,0) = e00; e(0,1) = e01; e(0,2) = e02; e(0,3) = e03;
      e(1,0) = e10; e(1,1) = e11; e(1,2) = e12; e(1,3) = e13;
      e(2,0) = e20; e(2,1) = e21; e(2,2) = e22; e(2,3) = e23;
      e(3,0) = e30; e(3,1) = e31; e(3,2) = e32; e(3,3) = e33;
    }
    //-----------------------------------------------------------------------------
    Matrix4& fill(T_scalar val)
    {
      e(0,0) = e(1,0) = e(2,0) = e(3,0) = 
      e(0,1) = e(1,1) = e(2,1) = e(3,1) = 
      e(0,2) = e(1,2) = e(2,2) = e(3,2) = 
      e(0,3) = e(1,3) = e(2,3) = e(3,3) = val;
      return *this;
    }
    //-----------------------------------------------------------------------------
    T_scalar diff(const Matrix4& other) const
    {
      T_scalar err = 0;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          if (e(j,i) > other.e(j,i)) // avoid fabs/abs
            err += e(j,i) - other.e(j,i);
          else
            err += other.e(j,i) - e(j,i);
      return err;
    }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar> getX() const
    {
      return Vector3<T_scalar>(mVec[0].x(), mVec[0].y(), mVec[0].z());
    }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar> getY() const
    {
      return Vector3<T_scalar>(mVec[1].x(), mVec[1].y(), mVec[1].z());
    }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar> getZ() const
    {
      return Vector3<T_scalar>(mVec[2].x(), mVec[2].y(), mVec[2].z());
    }
    //-----------------------------------------------------------------------------
    Vector3<T_scalar> getT() const
    {
      return Vector3<T_scalar>(mVec[3].x(), mVec[3].y(), mVec[3].z());
    }
    //-----------------------------------------------------------------------------
    Matrix4& setX(const Vector3<T_scalar>& v) 
    {
      mVec[0].x() = v.x();
      mVec[0].y() = v.y();
      mVec[0].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& setY(const Vector3<T_scalar>& v) 
    {
      mVec[1].x() = v.x();
      mVec[1].y() = v.y();
      mVec[1].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& setZ(const Vector3<T_scalar>& v) 
    {
      mVec[2].x() = v.x();
      mVec[2].y() = v.y();
      mVec[2].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& setT(const Vector3<T_scalar>& v) 
    {
      mVec[3].x() = v.x();
      mVec[3].y() = v.y();
      mVec[3].z() = v.z();
      return *this;
    }
    //-----------------------------------------------------------------------------
    bool operator==(const Matrix4& m) const
    {
      return memcmp(m.mVec, mVec, sizeof(T_scalar)*4*4) == 0;
    }
    //-----------------------------------------------------------------------------
    bool operator!=(const Matrix4& m) const
    {
      return !operator==(m);
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator=(const Matrix4& m)
    {
      memcpy(mVec, m.mVec, sizeof(T_scalar)*16);
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator+(const Matrix4& m) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t.e(j,i) = e(j,i) + m.e(j,i);

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator+=(const Matrix4& m)
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(j,i) += m.e(i,j);
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator-(const Matrix4& m) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t.e(j,i) = e(j,i) - m.e(j,i);

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator-=(const Matrix4& m)
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(j,i) -= m.e(i,j);
      return *this;
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
          t.e(j,i) = -e(j,i);
      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator+(T_scalar d) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t.e(j,i) = e(j,i) + d;
      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator+=(T_scalar d)
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(j,i) += d;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator-(T_scalar d) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t.e(j,i) = e(j,i) - d;
      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator-=(T_scalar d)
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(j,i) -= d;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator*(T_scalar d) const
    {
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t.e(j,i) = e(j,i) * d;
      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator*=(T_scalar d)
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(j,i) *= d;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 operator/(T_scalar d) const
    {
      d = (T_scalar)1 / d;
      Matrix4 t;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          t.e(j,i) = e(j,i) * d;
      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix4& operator/=(T_scalar d)
    {
      d = (T_scalar)1 / d;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          e(j,i) *= d;
      return *this;
    }
    //-----------------------------------------------------------------------------
    bool isIdentity() const
    {
      Matrix4 i;
      return memcmp(ptr(), i.ptr(), sizeof(T_scalar)*16) == 0;
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
    Matrix3<T_scalar> get3x3() const
    {
      Matrix3<T_scalar> t;
      t.e(0,0) = e(0,0); t.e(1,0) = e(1,0); t.e(2,0) = e(2,0);
      t.e(0,1) = e(0,1); t.e(1,1) = e(1,1); t.e(2,1) = e(2,1);
      t.e(0,2) = e(0,2); t.e(1,2) = e(1,2); t.e(2,2) = e(2,2);
      return t;
    }
    //-----------------------------------------------------------------------------
    //! This writes only on the upper 3x3 part of the matrix without touching the last row and column. 
    void set3x3(const Matrix3<T_scalar>& m)
    {
      e(0,0) = m.e(0,0); e(1,0) = m.e(1,0); e(2,0) = m.e(2,0);
      e(0,1) = m.e(0,1); e(1,1) = m.e(1,1); e(2,1) = m.e(2,1);
      e(0,2) = m.e(0,2); e(1,2) = m.e(1,2); e(2,2) = m.e(2,2);
    }
    //-----------------------------------------------------------------------------
    T_scalar* ptr()
    {
      return &e(0,0);
    }
    //-----------------------------------------------------------------------------
    const T_scalar* ptr() const
    {
      return &e(0,0);
    }
    //-----------------------------------------------------------------------------
    Matrix4& transpose()
    {
      T_scalar tmp;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
        {
          tmp = e(j,i);
          e(j,i) = e(i,j);
          e(i,j) = tmp;
        }
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4 getTransposed() const
    {
      Matrix4 m;
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          m.e(j,i) = e(i,j);
      return m;
    }
    //-----------------------------------------------------------------------------
    Matrix4& getTransposed(Matrix4& dest) const
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          dest.e(j,i) = e(i,j);
      return dest;
    }
    //-----------------------------------------------------------------------------
    bool isNull() const
    {
      for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
          if(e(i,j) != 0)
            return false;
      return true;
    }
    //-----------------------------------------------------------------------------
    Matrix4& setNull() 
    {
      fill(0);
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4& getNull(Matrix4& out)
    {
      out.fill(0);
      return out;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getNull()
    {
      return Matrix4().fill(0);
    }
    //-----------------------------------------------------------------------------
    Matrix4& setIdentity()
    {
      static const T_scalar I4d[] = 
      {
        (T_scalar)1, (T_scalar)0, (T_scalar)0, (T_scalar)0, 
        (T_scalar)0, (T_scalar)1, (T_scalar)0, (T_scalar)0, 
        (T_scalar)0, (T_scalar)0, (T_scalar)1, (T_scalar)0, 
        (T_scalar)0, (T_scalar)0, (T_scalar)0, (T_scalar)1 
      };
      memcpy(mVec, I4d, sizeof(T_scalar)*16);
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getIdentity()
    {
      return Matrix4();
    }
    //-----------------------------------------------------------------------------
    static Matrix4& getIdentity(Matrix4& out)
    {
      out.setIdentity();
      return out;
    }
    //-----------------------------------------------------------------------------
    T_scalar getInverse(Matrix4& dest) const;
    //-----------------------------------------------------------------------------
    Matrix4 getInverse(T_scalar *determinant=NULL) const
    {
      Matrix4 tmp;
      T_scalar det = getInverse(tmp);
      if (determinant)
        *determinant = det;
      return tmp;
    }
    //-----------------------------------------------------------------------------
    Matrix4& invert(T_scalar *determinant=NULL)
    {
      T_scalar det = getInverse(*this);
      if (determinant)
        *determinant = det;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getPerspective(T_scalar fovy, T_scalar aspect_ratio, T_scalar znear, T_scalar zfar);
    //-----------------------------------------------------------------------------
    static Matrix4 getFrustum(T_scalar pleft, T_scalar pright, T_scalar pbottom, T_scalar ptop, T_scalar pnear, T_scalar pfar);
    //-----------------------------------------------------------------------------
    static Matrix4 getOrtho(T_scalar pleft, T_scalar pright, T_scalar pbottom, T_scalar ptop, T_scalar pnear, T_scalar pfar);
    //-----------------------------------------------------------------------------
    static Matrix4 getOrtho2D(T_scalar pleft, T_scalar pright, T_scalar pbottom, T_scalar ptop);
    //-----------------------------------------------------------------------------
    static Matrix4 getLookAt(const Vector3<T_scalar>& eye, const Vector3<T_scalar>& look, const Vector3<T_scalar>& up);
    //-----------------------------------------------------------------------------
    void getAsLookAt(Vector3<T_scalar>& eye, Vector3<T_scalar>& look, Vector3<T_scalar>& up, Vector3<T_scalar>& right) const;
    //-----------------------------------------------------------------------------
    void getYXRotationAngles(T_scalar& degrees_y, T_scalar& degrees_x) const;
    //-----------------------------------------------------------------------------
    static Matrix4& getRotation(Matrix4& out, T_scalar degrees, T_scalar x, T_scalar y, T_scalar z);
    //-----------------------------------------------------------------------------
    static Matrix4 getRotation(T_scalar degrees, T_scalar x, T_scalar y, T_scalar z)
    {
      Matrix4 m;
      return getRotation(m, degrees, x, y, z);
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getRotation(T_scalar degrees, const Vector3<T_scalar>& v)
    {
      return getRotation(degrees, v.x(), v.y(), v.z());
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getRotation(T_scalar degrees1, const Vector3<T_scalar>& v1, T_scalar degrees2, const Vector3<T_scalar>& v2)
    {
      return getRotation(degrees1, v1.x(), v1.y(), v1.z()) * getRotation(degrees2, v2.x(), v2.y(), v2.z());
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getRotation(T_scalar degrees1, const Vector3<T_scalar>& v1, T_scalar degrees2, const Vector3<T_scalar>& v2, T_scalar degrees3, const Vector3<T_scalar>& v3)
    {
      return getRotation(degrees1, v1.x(), v1.y(), v1.z()) * getRotation(degrees2, v2.x(), v2.y(), v2.z()) * getRotation(degrees3, v3.x(), v3.y(), v3.z());
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate(T_scalar degrees, const Vector3<T_scalar>& v)
    {
      return rotate(degrees, v.x(), v.y(), v.z());
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate(T_scalar degrees, T_scalar x, T_scalar y, T_scalar z)
    {
      *this = getRotation(degrees, x, y, z) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate(T_scalar degrees1, const Vector3<T_scalar>& v1, T_scalar degrees2, const Vector3<T_scalar>& v2)
    {
      *this = getRotation(degrees1, v1, degrees2, v2) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate(T_scalar degrees1, const Vector3<T_scalar>& v1, T_scalar degrees2, const Vector3<T_scalar>& v2, T_scalar degrees3, const Vector3<T_scalar>& v3)
    {
      *this = getRotation(degrees1, v1, degrees2, v2, degrees3, v3) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getRotationXYZ(T_scalar degX, T_scalar degY, T_scalar degZ)
    {
      return getRotation(degX, 1,0,0) * getRotation(degY, 0,1,0) * getRotation(degZ, 0,0,1);
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotateXYZ(T_scalar degX, T_scalar degY, T_scalar degZ)
    {
      *this = getRotationXYZ(degX, degY, degZ) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getRotationZYX(T_scalar degZ, T_scalar degY, T_scalar degX)
    {
      return getRotation(degZ, 0,0,1) * getRotation(degY, 0,1,0) * getRotation(degX, 1,0,0);
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotateZYX(T_scalar degZ, T_scalar degY, T_scalar degX)
    {
      *this = getRotationZYX(degZ, degY, degX) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4& getRotation(Matrix4& out, const Vector3<T_scalar>& from, const Vector3<T_scalar>& to);
    //-----------------------------------------------------------------------------
    static Matrix4 getRotation(const Vector3<T_scalar>& from, const Vector3<T_scalar>& to)
    {
      Matrix4 m;
      return getRotation(m, from, to);
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate(const Vector4<T_scalar>& from, const Vector4<T_scalar>& to)
    {
      *this = getRotation(from, to) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& rotate(const Vector3<T_scalar>& from, const Vector3<T_scalar>& to)
    {
      *this = getRotation(from, to) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4& getTranslation(Matrix4&out, const Vector3<T_scalar>& v)
    {
      return getTranslation(out, v.x(), v.y(), v.z());
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getTranslation(const Vector3<T_scalar>& v)
    {
      Matrix4 m;
      return getTranslation(m, v.x(), v.y(), v.z());
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getTranslation(T_scalar x, T_scalar y, T_scalar z)
    {
      Matrix4 m;
      return getTranslation(m, x, y, z);
    }
    //-----------------------------------------------------------------------------
    static Matrix4& getTranslation(Matrix4& out, T_scalar x, T_scalar y, T_scalar z)
    {
      out.setIdentity();
      out.e(0,3) = x;
      out.e(1,3) = y;
      out.e(2,3) = z;
      return out;
    }
    //-----------------------------------------------------------------------------
    Matrix4& translate(T_scalar x, T_scalar y, T_scalar z)
    {
      *this = getTranslation(x,y,z) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& translate(const Vector3<T_scalar>& v)
    {
      *this = getTranslation(v) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix4& getScaling(Matrix4& out, const Vector3<T_scalar>& v)
    {
      return getScaling(out, v.x(), v.y(), v.z());
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getScaling(const Vector3<T_scalar>& v)
    {
      Matrix4 m;
      return getScaling(m, v.x(), v.y(), v.z());
    }
    //-----------------------------------------------------------------------------
    static Matrix4 getScaling(T_scalar x, T_scalar y, T_scalar z)
    {
      Matrix4 m;
      return getScaling(m, x, y, z);
    }
    //-----------------------------------------------------------------------------
    static Matrix4& getScaling(Matrix4& out, T_scalar x, T_scalar y, T_scalar z)
    {
      out.setIdentity();
      out.e(0,0) = x;
      out.e(1,1) = y;
      out.e(2,2) = z;
      return out;
    }
    //-----------------------------------------------------------------------------
    Matrix4& scale(T_scalar x, T_scalar y, T_scalar z)
    {
      *this = getScaling(x,y,z) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix4& scale(const Vector3<T_scalar> v)
    {
      *this = getScaling(v.x(), v.y(), v.z()) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------

    const T_scalar& e(int i, int j) const { return mVec[j][i]; }
    T_scalar& e(int i, int j) { return mVec[j][i]; }

  private:
    const Vector4<T_scalar>& operator[](unsigned int i) const { VL_CHECK(i<4); return mVec[i]; }
    Vector4<T_scalar>& operator[](unsigned int i) { VL_CHECK(i<4); return mVec[i]; }

  protected:
    Vector4<T_scalar> mVec[4];
  };
  //-----------------------------------------------------------------------------
  // OPERATORS
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  inline Matrix4<T_scalar> operator*(const Matrix4<T_scalar>& m2, const Matrix4<T_scalar>& m1)
  {
    Matrix4<T_scalar> t;
    t.e(0,0) = m1.e(0,0)*m2.e(0,0) + m1.e(1,0)*m2.e(0,1) + m1.e(2,0)*m2.e(0,2) + m1.e(3,0)*m2.e(0,3);
    t.e(0,1) = m1.e(0,1)*m2.e(0,0) + m1.e(1,1)*m2.e(0,1) + m1.e(2,1)*m2.e(0,2) + m1.e(3,1)*m2.e(0,3);
    t.e(0,2) = m1.e(0,2)*m2.e(0,0) + m1.e(1,2)*m2.e(0,1) + m1.e(2,2)*m2.e(0,2) + m1.e(3,2)*m2.e(0,3);
    t.e(0,3) = m1.e(0,3)*m2.e(0,0) + m1.e(1,3)*m2.e(0,1) + m1.e(2,3)*m2.e(0,2) + m1.e(3,3)*m2.e(0,3);

    t.e(1,0) = m1.e(0,0)*m2.e(1,0) + m1.e(1,0)*m2.e(1,1) + m1.e(2,0)*m2.e(1,2) + m1.e(3,0)*m2.e(1,3);
    t.e(1,1) = m1.e(0,1)*m2.e(1,0) + m1.e(1,1)*m2.e(1,1) + m1.e(2,1)*m2.e(1,2) + m1.e(3,1)*m2.e(1,3);
    t.e(1,2) = m1.e(0,2)*m2.e(1,0) + m1.e(1,2)*m2.e(1,1) + m1.e(2,2)*m2.e(1,2) + m1.e(3,2)*m2.e(1,3);
    t.e(1,3) = m1.e(0,3)*m2.e(1,0) + m1.e(1,3)*m2.e(1,1) + m1.e(2,3)*m2.e(1,2) + m1.e(3,3)*m2.e(1,3);

    t.e(2,0) = m1.e(0,0)*m2.e(2,0) + m1.e(1,0)*m2.e(2,1) + m1.e(2,0)*m2.e(2,2) + m1.e(3,0)*m2.e(2,3);
    t.e(2,1) = m1.e(0,1)*m2.e(2,0) + m1.e(1,1)*m2.e(2,1) + m1.e(2,1)*m2.e(2,2) + m1.e(3,1)*m2.e(2,3);
    t.e(2,2) = m1.e(0,2)*m2.e(2,0) + m1.e(1,2)*m2.e(2,1) + m1.e(2,2)*m2.e(2,2) + m1.e(3,2)*m2.e(2,3);
    t.e(2,3) = m1.e(0,3)*m2.e(2,0) + m1.e(1,3)*m2.e(2,1) + m1.e(2,3)*m2.e(2,2) + m1.e(3,3)*m2.e(2,3);

    t.e(3,0) = m1.e(0,0)*m2.e(3,0) + m1.e(1,0)*m2.e(3,1) + m1.e(2,0)*m2.e(3,2) + m1.e(3,0)*m2.e(3,3);
    t.e(3,1) = m1.e(0,1)*m2.e(3,0) + m1.e(1,1)*m2.e(3,1) + m1.e(2,1)*m2.e(3,2) + m1.e(3,1)*m2.e(3,3);
    t.e(3,2) = m1.e(0,2)*m2.e(3,0) + m1.e(1,2)*m2.e(3,1) + m1.e(2,2)*m2.e(3,2) + m1.e(3,2)*m2.e(3,3);
    t.e(3,3) = m1.e(0,3)*m2.e(3,0) + m1.e(1,3)*m2.e(3,1) + m1.e(2,3)*m2.e(3,2) + m1.e(3,3)*m2.e(3,3);
    return t;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  inline Matrix4<T_scalar> operator+(T_scalar d, const Matrix4<T_scalar>& m)
  {
    return m + d;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  inline Matrix4<T_scalar> operator*(T_scalar d, const Matrix4<T_scalar>& m)
  {
    return m * d;
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  template<typename T_scalar>
  inline Vector4<T_scalar> operator*(const Matrix4<T_scalar>& m, const Vector4<T_scalar>& v)
  {
    return Vector4<T_scalar>(
      v.x()*m.e(0,0) + v.y()*m.e(0,1) + v.z()*m.e(0,2) + v.w()*m.e(0,3),
      v.x()*m.e(1,0) + v.y()*m.e(1,1) + v.z()*m.e(1,2) + v.w()*m.e(1,3),
      v.x()*m.e(2,0) + v.y()*m.e(2,1) + v.z()*m.e(2,2) + v.w()*m.e(2,3),
      v.x()*m.e(3,0) + v.y()*m.e(3,1) + v.z()*m.e(3,2) + v.w()*m.e(3,3)
   );
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  //! The incoming vector is considered a Vector4<T_scalar> with the component w = 1
  template<typename T_scalar>
  inline Vector3<T_scalar> operator*(const Matrix4<T_scalar>& m, const Vector3<T_scalar>& v)
  {
    return Vector3<T_scalar>(
      v.x()*m.e(0,0) + v.y()*m.e(0,1) + v.z()*m.e(0,2) + /*1**/m.e(0,3),
      v.x()*m.e(1,0) + v.y()*m.e(1,1) + v.z()*m.e(1,2) + /*1**/m.e(1,3),
      v.x()*m.e(2,0) + v.y()*m.e(2,1) + v.z()*m.e(2,2) + /*1**/m.e(2,3)
   );
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  //! The incoming vector is considered a Vector4<T_scalar> with components: z = 0 and w = 1
  template<typename T_scalar>
  inline Vector2<T_scalar> operator*(const Matrix4<T_scalar>& m, const Vector2<T_scalar>& v)
  {
    return Vector2<T_scalar>(
      v.x()*m.e(0,0) + v.y()*m.e(0,1) + /*0*m.e(0,2) +*/ /*1**/m.e(0,3),
      v.x()*m.e(1,0) + v.y()*m.e(1,1) + /*0*m.e(1,2) +*/ /*1**/m.e(1,3)
   );
  }
  //-----------------------------------------------------------------------------
  //! pre-multiplication: row vector * matrix
  template<typename T_scalar>
  inline Vector4<T_scalar> operator*(const Vector4<T_scalar>& v, const Matrix4<T_scalar>& m)
  {
    return Vector4<T_scalar>(
      v.x()*m.e(0,0) + v.y()*m.e(1,0) + v.z()*m.e(2,0) + v.w()*m.e(3,0),
      v.x()*m.e(0,1) + v.y()*m.e(1,1) + v.z()*m.e(2,1) + v.w()*m.e(3,1),
      v.x()*m.e(0,2) + v.y()*m.e(1,2) + v.z()*m.e(2,2) + v.w()*m.e(3,2),
      v.x()*m.e(0,3) + v.y()*m.e(1,3) + v.z()*m.e(2,3) + v.w()*m.e(3,3)
   );
  }
  //-----------------------------------------------------------------------------
  //! pre-multiplication: row vector * matrix
  //! The incoming vector is considered a Vector4<T_scalar> with the component w = 1
  template<typename T_scalar>
  inline Vector3<T_scalar> operator*(const Vector3<T_scalar>& v, const Matrix4<T_scalar>& m)
  {
    return Vector3<T_scalar>(
      v.x()*m.e(0,0) + v.y()*m.e(1,0) + v.z()*m.e(2,0) + /*1**/m.e(3,0),
      v.x()*m.e(0,1) + v.y()*m.e(1,1) + v.z()*m.e(2,1) + /*1**/m.e(3,1),
      v.x()*m.e(0,2) + v.y()*m.e(1,2) + v.z()*m.e(2,2) + /*1**/m.e(3,2)
   );
  }
  //-----------------------------------------------------------------------------
  //! pre-multiplication: row vector * matrix
  //! The incoming vector is considered a Vector4<T_scalar> with components: z = 0 and w = 1
  template<typename T_scalar>
  inline Vector2<T_scalar> operator*(const Vector2<T_scalar>& v, const Matrix4<T_scalar>& m)
  {
    return Vector2<T_scalar>(
      v.x()*m.e(0,0) + v.y()*m.e(1,0) + /*0*m.e(2,0) +*/ /*1**/m.e(3,0),
      v.x()*m.e(0,1) + v.y()*m.e(1,1) + /*0*m.e(2,1) +*/ /*1**/m.e(3,1)
   );
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  Matrix4<T_scalar> Matrix4<T_scalar>::getLookAt(const Vector3<T_scalar>& eye, const Vector3<T_scalar>& look, const Vector3<T_scalar>& up)
  {
    Vector3<T_scalar> y = Vector3<T_scalar>(up).normalize();
    Vector3<T_scalar> z = (eye - look).normalize(); // == -(look-eye)
    Vector3<T_scalar> x = cross(y,z).normalize();
    y = cross(z, x).normalize();
    
    Matrix4<T_scalar> m;

    m.setT(eye);
    m.setX(x);
    m.setY(y);
    m.setZ(z);

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  void Matrix4<T_scalar>::getAsLookAt(Vector3<T_scalar>& eye, Vector3<T_scalar>& look, Vector3<T_scalar>& up, Vector3<T_scalar>& right) const
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
  template<typename T_scalar>
  Matrix4<T_scalar> Matrix4<T_scalar>::getPerspective(T_scalar fovy, T_scalar aspect_ratio, T_scalar znear, T_scalar zfar)
  {
    Matrix4<T_scalar> m;

    T_scalar rads = (fovy / ((T_scalar)2)) * (T_scalar)dDEG_TO_RAD;
    T_scalar dz = zfar - znear;
    T_scalar sa = sin(rads);
    if ((dz == 0) || (sa == 0) || (aspect_ratio == 0)) 
      return m * 0;
    T_scalar ctan = cos(rads) / sa;

    m.e(0,0) = (T_scalar)(ctan / aspect_ratio);
    m.e(1,1) = (T_scalar)(ctan);
    m.e(2,2) = (T_scalar)(-(zfar + znear) / dz);
    m.e(3,2) = -((T_scalar)1);
    m.e(2,3) = (T_scalar)(-((T_scalar)2) * znear * zfar / dz);
    m.e(3,3) = 0;

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  Matrix4<T_scalar> Matrix4<T_scalar>::getFrustum(T_scalar left, T_scalar right, T_scalar bottom, T_scalar top, T_scalar pnear, T_scalar pfar)
  {
    Matrix4<T_scalar> m;

    if (pnear <= 0 || pfar <= 0 || pnear == pfar || left == right || top == bottom)
      return m * 0;

    T_scalar x =  (((T_scalar)2)*pnear)  / (right-left);
    T_scalar y =  (((T_scalar)2)*pnear)  / (top-bottom);
    T_scalar a =  (right+left) / (right-left);
    T_scalar b =  (top+bottom) / (top-bottom);
    T_scalar c = -(pfar+pnear)   / (pfar-pnear);
    T_scalar d = -(((T_scalar)2)*pfar*pnear) / (pfar-pnear);

    m.e(0,0) = x;  m.e(0,1) = 0;  m.e(0,2) = a;    m.e(0,3) = 0;
    m.e(1,0) = 0;  m.e(1,1) = y;  m.e(1,2) = b;    m.e(1,3) = 0;
    m.e(2,0) = 0;  m.e(2,1) = 0;  m.e(2,2) = c;    m.e(2,3) = d;
    m.e(3,0) = 0;  m.e(3,1) = 0;  m.e(3,2) = -((T_scalar)1); m.e(3,3) = 0;

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  Matrix4<T_scalar> Matrix4<T_scalar>::getOrtho(T_scalar left, T_scalar right, T_scalar bottom, T_scalar top, T_scalar pnear, T_scalar pfar)
  {
    Matrix4<T_scalar> m;

    m.e(0,0) = ((T_scalar)2) / (right-left);
    m.e(0,1) = 0;
    m.e(0,2) = 0;
    m.e(0,3) = -(right+left) / (right-left);

    m.e(1,0) = 0;
    m.e(1,1) = ((T_scalar)2) / (top-bottom);
    m.e(1,2) = 0;
    m.e(1,3) = -(top+bottom) / (top-bottom);

    m.e(2,0) = 0;
    m.e(2,1) = 0;
    m.e(2,2) = -((T_scalar)2) / (pfar-pnear);
    m.e(2,3) = -(pfar+pnear) / (pfar-pnear);

    m.e(3,0) = 0;
    m.e(3,1) = 0;
    m.e(3,2) = 0;
    m.e(3,3) = ((T_scalar)1);

    return m;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  Matrix4<T_scalar> Matrix4<T_scalar>::getOrtho2D(T_scalar left, T_scalar right, T_scalar bottom, T_scalar top)
  {
    return getOrtho(left, right, bottom, top, -1, +1);
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  Matrix4<T_scalar>& Matrix4<T_scalar>::getRotation(Matrix4<T_scalar>& out, T_scalar degrees, T_scalar x, T_scalar y, T_scalar z)
  {
    out.setIdentity();

    if (degrees == 0 || (x == 0 && y ==0 && z == 0))
      return out;
      
    degrees = T_scalar(degrees * dDEG_TO_RAD);

    T_scalar xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;

    s = (T_scalar) sin(degrees);
    c = (T_scalar) cos(degrees);

    // simple cases
    if (x == 0) 
    {
      if (y == 0) 
      {
        if (z != 0) 
        {
          // rotate only around z-axis
          out.e(0,0) = (T_scalar)c;
          out.e(1,1) = (T_scalar)c;
          if (z < 0) 
          {
            out.e(1,0) = -(T_scalar)s;
            out.e(0,1) = (T_scalar)s;
          }
          else 
          {
            out.e(1,0) = (T_scalar)s;
            out.e(0,1) = -(T_scalar)s;
          }
          return out;
        }
      }
      else if (z == 0) 
      {
        // rotate only around y-axis
        out.e(0,0) = (T_scalar)c;
        out.e(2,2) = (T_scalar)c;
        if (y < 0) 
        {
          out.e(2,0) = (T_scalar)s;
          out.e(0,2) = -(T_scalar)s;
        }
        else 
        {
          out.e(2,0) = -(T_scalar)s;
          out.e(0,2) = (T_scalar)s;
        }
        return out;
      }
    }
    else if (y == 0) 
    {
      if (z == 0) 
      {
        // rotate only around x-axis
        out.e(1,1) = (T_scalar)c;
        out.e(2,2) = (T_scalar)c;
        if (x < 0) 
        {
          out.e(2,1) = -(T_scalar)s;
          out.e(1,2) = (T_scalar)s;
        }
        else 
        {
          out.e(2,1) = (T_scalar)s;
          out.e(1,2) = -(T_scalar)s;
        }
        return out;
      }
    }

    // Beginning of general axisa to matrix conversion
    T_scalar dot = x*x + y*y + z*z;

    if (dot > (T_scalar)((T_scalar)1.0001) || dot < (T_scalar)0.99999) 
    {
      T_scalar mag = (T_scalar) sqrt(dot);
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
    one_c = ((T_scalar)1) - c;

    out.e(0,0) = (T_scalar)((one_c * xx) + c); out.e(1,0) = (T_scalar)((one_c * xy) + zs); out.e(2,0) = (T_scalar)((one_c * zx) - ys);
    out.e(0,1) = (T_scalar)((one_c * xy) - zs); out.e(1,1) = (T_scalar)((one_c * yy) + c); out.e(2,1) = (T_scalar)((one_c * yz) + xs);
    out.e(0,2) = (T_scalar)((one_c * zx) + ys); out.e(1,2) = (T_scalar)((one_c * yz) - xs); out.e(2,2) = (T_scalar)((one_c * zz) + c);
    return out;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  T_scalar Matrix4<T_scalar>::getInverse(Matrix4<T_scalar>& dest) const
  {
    if (&dest == this)
    {
      Matrix4<T_scalar> tmp;
      T_scalar det = getInverse(tmp);
      dest = tmp;
      return det;
    }
    else
    {
      int i,j,k;
      int pvt_i[4], pvt_j[4];
      T_scalar pvt_val;
      T_scalar tmp;
      T_scalar det;

      dest = *this; // memcpy(dest, mVec, sizeof(T_scalar)*16);

      det = ((T_scalar)1);
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
          if (i!=k) dest[i][k]/=(-pvt_val);
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

        dest[k][k] = ((T_scalar)1)/pvt_val;
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
  template<typename T_scalar>
  Matrix4<T_scalar>& Matrix4<T_scalar>::getRotation(Matrix4<T_scalar>& out, const Vector3<T_scalar>& from, const Vector3<T_scalar>& to)
  {
    Vector3<T_scalar> a,b;
    a = from;
    b = to;
    a.normalize();
    b.normalize();
    T_scalar cosa = dot(a,b);
    cosa = clamp(cosa,-((T_scalar)1),+((T_scalar)1));
    Vector3<T_scalar> axis,n2;
    axis = cross(a,b);
    axis.normalize();
    T_scalar alpha = acos(cosa);
    return getRotation(out, alpha*(T_scalar)dRAD_TO_DEG, axis.x(), axis.y(), axis.z());
  }
  //-----------------------------------------------------------------------------
  //! If this matrix can be represented as \p RY(degrees_y) * \p RX(degrees_x), where 
  //! RX and RY are getRotation matrices around the X and Y axis respectively, this 
  //! function returns the getRotation angles \p degrees_y and \p degrees_x.
  //! \note This function can only retrieve angles that satisfy the following conditions:
  //! - -180 <= degrees_y <= 180
  //! - -180 <= degrees_x <= 180 and degrees_x != 90
  template<typename T_scalar>
  void Matrix4<T_scalar>::getYXRotationAngles(T_scalar& degrees_y, T_scalar& degrees_x) const
  {
    Vector3<T_scalar> vx = getX();
    Vector3<T_scalar> vy = getY();
    Vector3<T_scalar> vz = getZ();

    vx.normalize();
    vy.normalize();
    vz.normalize();

    T_scalar kx = dot(vy,Vector3<T_scalar>(0,1,0));
    kx = clamp(kx,-((T_scalar)1),+((T_scalar)1));
    degrees_x = acos(kx) * (T_scalar)dRAD_TO_DEG;
    if(dot(vz, Vector3<T_scalar>(0,1,0)) > 0)
      degrees_x = -degrees_x;

    T_scalar ky = dot(vx, Vector3<T_scalar>(1,0,0));
    ky = clamp(ky,-((T_scalar)1),+((T_scalar)1));
    degrees_y = acos(ky) * (T_scalar)dRAD_TO_DEG;
    if(dot(vz, Vector3<T_scalar>(1,0,0)) < 0)
      degrees_y = -degrees_y;
    if (fabs(degrees_x) > (T_scalar)90)
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