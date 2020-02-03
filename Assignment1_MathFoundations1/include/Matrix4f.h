// High level design note
// Our matrix should match the behavior of the glm library.
#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <cmath>

// We need to Vector4f header in order to multiply a matrix
// by a vector.
#include "Vector4f.h"

// Matrix 4f represents 4x4 matrices in Math
struct Matrix4f{
public:
    float n[4][4];  // Store each value of the matrix
    Matrix4f() = default;

    // Row major order!
    // Matrix constructor with 9 scalar values.
    Matrix4f( float n00, float n01, float n02, float n03,
              float n10, float n11, float n12, float n13,
              float n20, float n21, float n22, float n23,
              float n30, float n31, float n32, float n33){

        n[0][0] = n00; n[0][1] = n01; n[0][2] = n02; n[0][3] = n03;
        n[1][0] = n10; n[1][1] = n11; n[1][2] = n12; n[1][3] = n13;
        n[2][0] = n20; n[2][1] = n21; n[2][2] = n22; n[2][3] = n23;
        n[3][0] = n30; n[3][1] = n31; n[3][2] = n32; n[3][3] = n33;
    }

    // Matrix constructor from four vectors.
    // Note: 'd' will almost always be 0,0,0,1
    Matrix4f(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d){
        init(a,b,c,d);
    }

    void init(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d){
      n[0][0] = a.x; n[1][0] = b.x; n[2][0] = c.x; n[3][0] = d.x;
      n[0][1] = a.y; n[1][1] = b.y; n[2][1] = c.y; n[3][1] = d.y;
      n[0][2] = a.z; n[1][2] = b.z; n[2][2] = c.z; n[3][2] = d.z;
      n[0][3] = a.w; n[1][3] = b.w; n[2][3] = c.w; n[3][3] = d.w;
    }

    // Makes the matrix an identity matrix
    void identity(){
        init(Vector4f(1,0,0,0),
             Vector4f(0,1,0,0),
             Vector4f(0,0,1,0),
             Vector4f(0,0,0,1));
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j){
      return (n[j][i]);
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const{
      return (n[i][j]);
    }

    // Return a single row vector from the matrix 
    Vector4f& operator [](int j){
      return (*reinterpret_cast<Vector4f *>(n[j]));
    }

    // Return a single row vector from the matrix 
    const Vector4f& operator [](int j) const{
      return (*reinterpret_cast<const Vector4f *>(n[j]));
    }

    // Make a matrix rotate about various axis
    Matrix4f MakeRotationX(float t){
        Matrix4f ret;
        ret.identity();
        ret.n[1][1] = cos(t);
        ret.n[1][2] = sin(t)*-1;
        ret.n[2][1] = sin(t);
        ret.n[2][2] = cos(t);

        return ret;
    }

    Matrix4f MakeRotationY(float t){
        Matrix4f ret;
        ret.identity();
        ret.n[0][0] = cos(t);
        ret.n[2][0] = sin(t)*-1;
        ret.n[0][2] = sin(t);
        ret.n[2][2] = cos(t);

        return ret;
    }
   
   Matrix4f MakeRotationZ(float t){
        Matrix4f ret;
        ret.identity();
        ret.n[0][0] = cos(t);
        ret.n[0][1] = sin(t)*-1;
        ret.n[1][0] = sin(t);
        ret.n[1][1] = cos(t);

        return ret;
    }
    
    Matrix4f MakeScale(float sx,float sy, float sz){
        Matrix4f ret;
        ret.identity();
        ret.n[0][0] = sx;
        ret.n[1][1] = sy;
        ret.n[2][2] = sz;

        return ret;
    }

    // Equality for testing
    bool operator==(const Matrix4f& other) {
        return (*this)[0] == other[0] &&
               (*this)[1] == other[1] &&
               (*this)[2] == other[2] &&
               (*this)[3] == other[3];
    }

private:
    // compare 2 floating point numbers for equality.
    bool fcomp(float f1, float f2, float epsilon) {
        return fabs(f1 - f2) < epsilon;
    }

    bool fcomp(float f1, float f2) {
        return fcomp(f1, f2, Vector4f_EPSILON);
    }
};

// Matrix Multiplication
Matrix4f operator *(const Matrix4f& A, const Matrix4f& B){
  // TODO:
  Matrix4f mat4;

  return mat4;
}

// Matrix multiply by a vector

Vector4f operator *(const Matrix4f& M, const Vector4f& v){
  // TODO:
  Vector4f vec;

  return vec;
}


// For Debugging!
std::ostream& operator<<(std::ostream& os, const Matrix4f& obj) {
    return os << "Matrix4f(" << obj[0] << "," << obj[1] << "," << obj[2] << "," << obj[3] <<")";
}

#endif
