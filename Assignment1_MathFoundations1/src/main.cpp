// Includes for the assignment
#include "Vector4f.h"
#include "Matrix4f.h"
#include <iostream>

// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Sample unit test comparing against GLM.
bool unitTest0(){
    glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
    Matrix4f myIdentity( 1.0f,0,0,0,
                         0,1.0f,0,0,
                         0,0,1.0f,0,
                         0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
    
    return false;    
}

bool unitTest1(){
    glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
    Matrix4f myIdentity( 1.0f,0,0,0,
                         0,1.0f,0,0,
                         0,0,1.0f,0,
                         0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity(0,0) &&
        glmIdentityMatrix[0][1]==myIdentity(0,1) &&
        glmIdentityMatrix[0][2]==myIdentity(0,2) &&
        glmIdentityMatrix[0][3]==myIdentity(0,3) &&
        glmIdentityMatrix[1][0]==myIdentity(1,0) &&
        glmIdentityMatrix[1][1]==myIdentity(1,1) &&
        glmIdentityMatrix[1][2]==myIdentity(1,2) &&
        glmIdentityMatrix[1][3]==myIdentity(1,3) &&
        glmIdentityMatrix[2][0]==myIdentity(2,0) &&
        glmIdentityMatrix[2][1]==myIdentity(2,1) &&
        glmIdentityMatrix[2][2]==myIdentity(2,2) &&
        glmIdentityMatrix[2][3]==myIdentity(2,3) &&
        glmIdentityMatrix[3][0]==myIdentity(3,0) &&
        glmIdentityMatrix[3][1]==myIdentity(3,1) &&
        glmIdentityMatrix[3][2]==myIdentity(3,2) &&
        glmIdentityMatrix[3][3]==myIdentity(3,3)){
            return true;
    }
    
    return false;    
}

// Sample unit test comparing against GLM.
bool unitTest2(){
    glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
    Vector4f a(1.0f ,0.0f,  0.0f,   0.0f);
    Vector4f b(0.0f ,1.0f,  0.0f,   0.0f);
    Vector4f c(0.0f ,0.0f,  1.0f,   0.0f);
    Vector4f d(0.0f ,0.0f,  0.0f,   1.0f);
    Matrix4f myIdentity(a,b,c,d);

    Matrix4f identity2(a,a,a,a);
    identity2.identity();
    bool assert1 = myIdentity == identity2;

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return assert1;
    }
    
    return false;    
}

// Sample unit test comparing against GLM.
// TODO: Test against glm::scale
bool unitTest3(){
    glm::mat4 glmScale = glm::mat4(2.0f);
    Vector4f a(1.0f,0,0,0);
    Vector4f b(0.0f,1.0f,0,0);
    Vector4f c(0,0,1.0f,0);
    Vector4f d(0,0,0,1.0f);
    Matrix4f myScaled(a,b,c,d);
    myScaled.MakeScale(2.0f,2.0f,2.0f);

    if(
        glmScale[0][0]==myScaled[0][0] &&
        glmScale[0][1]==myScaled[0][1] &&
        glmScale[0][2]==myScaled[0][2] &&
        glmScale[0][3]==myScaled[0][3] &&
        glmScale[1][0]==myScaled[1][0] &&
        glmScale[1][1]==myScaled[1][1] &&
        glmScale[1][2]==myScaled[1][2] &&
        glmScale[1][3]==myScaled[1][3] &&
        glmScale[2][0]==myScaled[2][0] &&
        glmScale[2][1]==myScaled[2][1] &&
        glmScale[2][2]==myScaled[2][2] &&
        glmScale[2][3]==myScaled[2][3] &&
        glmScale[3][0]==myScaled[3][0] &&
        glmScale[3][1]==myScaled[3][1] &&
        glmScale[3][2]==myScaled[3][2] &&
        glmScale[3][3]==myScaled[3][3]){
            return true;
    }
    
    return false;    
}

// Sample unit test comparing against GLM.
// Testing operator
bool unitTest4(){
    glm::mat4 glmTest = glm::mat4(1.0f);
    glmTest[1][3] = 72.0f;
    glmTest[2][3] = 2.1f;

    Matrix4f myMatrix(0,0,0,0,
                      0,0,0,0,
                      0,0,0,0,
                      0,0,0,0);

    myMatrix[1][3] = 72.0f;
    myMatrix[2][3] = 2.1f;

    if( glmTest[1][3]==myMatrix[1][3] &&
        glmTest[2][3]==myMatrix[2][3] ){
            return true;
    }
    
    return false;    
}

// Sample unit test testing your library
bool unitTest5(){
  Vector4f a(1,1,1,1);
  Vector4f b(0,0,0,0);
  Vector4f c = a + b;

  if(c.x == 1 && c.y == 1 && c.z ==1 && c.w==1){
    return true;
  }
    return false;
}


/*
    Vector Unit tests
*/


bool vecTestConstructor() {
    Vector4f v = Vector4f(1,2,3,4);
    bool assert1 = v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4;

    bool assert2 = Vector4f(0,0.0199987,0.9998,0) == Vector4f(0,0.0199987,0.9998,0);

    return assert1 && assert2;
}

bool vecTestScalarMultiply() {
    Vector4f v = Vector4f(1,2,3,4);
    Vector4f v1 = Vector4f(1,2,3,4);
    bool assert1 = v == v1;
    
    v *= 1;
    bool assert2 = v == v1;

    v1 *= 2;
    bool assert3 = !(v == v1);
    bool assert7 = !(v == v1);

    bool assert4 = (v *= 4) == (v1 *= 2);

    return assert1 && assert2 && assert3 && assert4;
}

bool vecTestScalarDivide() {
    Vector4f v = Vector4f(12, 24, 60, 0);
    Vector4f v1 = Vector4f(12, 24, 60, 0);
    
    bool assert1 = v == v1;
    
    v /= 1;
    bool assert2 = v == v1;

    v1 /= 2;
    bool assert3 = !(v == v1);
    bool assert4 = v1 == Vector4f(6,12,30,0);

    v /= 5;
    bool assert5 = v == Vector4f(2.4,4.8,12,0);

    return assert1 && assert2 && assert3 && assert4 && assert5;
}

bool vecTestPlusMinus() {
    Vector4f v = Vector4f(0,0,0,0);
    Vector4f v1 = Vector4f(1,0,1,0);
    Vector4f v2 = Vector4f(4,4,7,67);
    Vector4f v3 = Vector4f(2,0,2,0);

    bool assert1 = v == (v + v);
    bool assert2 = v1 == (v1 + v);

    bool assert3 = (v1 + v1) == v3;
    bool assert4 = (v3 - v1) == v1;
    bool assert5 = ((v3 - v1) - v1) == v;

    bool assert6 = (v1 + v2 - v1) == v2;
    bool assert7 = (v3 - v2) == Vector4f(-2,-4,-5,-67);

    return assert1 && assert2 && assert3 && assert4 && assert5 && assert6 && assert7;
}

bool vecTestDotProduct() {
    Vector4f v = Vector4f(0,0,0,0);
    Vector4f v1 = Vector4f(1,1,1,1);
    Vector4f v2 = Vector4f(1,2,3,4);

    bool assert1 = Dot(v, v) == 0;
    bool assert2 = Dot(v1, v) == 0;
    bool assert3 = Dot(v, v2) == 0;
    bool assert4 = Dot(v1, v1) == 4;
    bool assert5 = Dot(v2, v2) == (1+4+9+16);

    return assert1 && assert2 && assert3 && assert4 && assert5;
}

bool matTestRotation() {
    Matrix4f m1;
    m1.identity();

    Matrix4f m2 = Matrix4f(Vector4f(1,0,0,0),
                           Vector4f(0,0.9998,-0.0199987,0),
                           Vector4f(0,0.0199987,0.9998,0),
                           Vector4f(0,0,0,1));

    return m1.MakeRotationX(0.02) == m2;
}

int main(){
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0: " << unitTest0() << " \n";
    std::cout << "Passed 1: " << unitTest1() << " \n";
    std::cout << "Passed 2: " << unitTest2() << " \n";
    std::cout << "Passed 3: " << unitTest3() << " \n";
    std::cout << "Passed 4: " << unitTest4() << " \n";
    std::cout << "Passed 5: " << unitTest5() << " \n";
    
    std::cout << "Passed vec: " << vecTestConstructor() << " \n";
    std::cout << "Passed vec: " << vecTestScalarMultiply() << " \n";
    std::cout << "Passed vec: " << vecTestScalarDivide() << " \n";
    std::cout << "Passed vec: " << vecTestPlusMinus() << " \n";
    std::cout << "Passed vec: " << vecTestDotProduct() << " \n";

    std::cout << "Passed mat: " << matTestRotation() << " \n";

    return 0;
}
