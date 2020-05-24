#ifndef YASMATHLIB_HPP
#define YASMATHLIB_HPP

#include<cmath>

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

// I'm using column-major order
//
//  _________           ___        ____
// | 1 1 1 1 |         | x |      | x' |
// | 1 1 1 1 |   \ /   | y |  --- | y' |
// | 1 1 1 1 |    *    | z |  --- | z' |
// | 1 1 1 1 |   / \   | w |      | w' |
//  '''''''''           '''        ''''

//namespace YasMathsLib {
struct Vector4F {
    float x;
    float y;
    float z;
    float w;
} typedef Vector4F, Vec4F;

struct Vector3F {
    float x;
    float y;
    float z;
} typedef Vector3F, Vec3F;

struct Matrix4F {
    float x1, y1, z1, w1;
    float x2, y2, z2, w2;
    float x3, y3, z3, w3;
    float x4, y4, z4, w4;
} typedef Mat4;

struct Matrix4GLF {
    GLfloat x1, y1, z1, w1;
    GLfloat x2, y2, z2, w2;
    GLfloat x3, y3, z3, w3;
    GLfloat x4, y4, z4, w4;
} typedef Mat4GLF;

static Matrix4F multiplyAbyB(Matrix4F a, Matrix4F b)
{
    Matrix4F mat = {
        a.x1*b.x1 + a.y1*b.x2 + a.z1*b.x3 + a.w1*b.x4, /*|*/ a.x1*b.y1 + a.y1*b.y2 + a.z1*b.y3 + a.w1*b.y4, /*|*/ a.x1*b.z1 + a.y1*b.z2 + a.z1*b.z3 + a.w1*b.z4, /*|*/ a.x1*b.w1 + a.y1*b.w2 + a.z1*b.w3 + a.w1*b.w4,
        a.x2*b.x1 + a.y2*b.x2 + a.z2*b.x3 + a.w2*b.x4, /*|*/ a.x2*b.y1 + a.y2*b.y2 + a.z2*b.y3 + a.w2*b.y4, /*|*/ a.x2*b.z1 + a.y2*b.z2 + a.z2*b.z3 + a.w2*b.z4, /*|*/ a.x2*b.w1 + a.y2*b.w2 + a.z2*b.w3 + a.w2*b.w4,
        a.x3*b.x1 + a.y3*b.x2 + a.z3*b.x3 + a.w3*b.x4, /*|*/ a.x3*b.y1 + a.y3*b.y2 + a.z3*b.y3 + a.w3*b.y4, /*|*/ a.x3*b.z1 + a.y3*b.z2 + a.z3*b.z3 + a.w3*b.z4, /*|*/ a.x3*b.w1 + a.y3*b.w2 + a.z3*b.w3 + a.w3*b.w4,
        a.x4*b.x1 + a.y4*b.x2 + a.z4*b.x3 + a.w4*b.x4, /*|*/ a.x4*b.y1 + a.y4*b.y2 + a.z4*b.y3 + a.w4*b.y4, /*|*/ a.x4*b.z1 + a.y4*b.z2 + a.z4*b.z3 + a.w4*b.z4, /*|*/ a.x4*b.w1 + a.y4*b.w2 + a.z4*b.w3 + a.w4*b.w4
    };
    return mat;
}

static Matrix4GLF multiplyAbyB(Matrix4GLF a, Matrix4GLF b)
{
    Matrix4GLF mat = {
        a.x1*b.x1 + a.y1*b.x2 + a.z1*b.x3 + a.w1*b.x4, /*|*/ a.x1*b.y1 + a.y1*b.y2 + a.z1*b.y3 + a.w1*b.y4, /*|*/ a.x1*b.z1 + a.y1*b.z2 + a.z1*b.z3 + a.w1*b.z4, /*|*/ a.x1*b.w1 + a.y1*b.w2 + a.z1*b.w3 + a.w1*b.w4,
        a.x2*b.x1 + a.y2*b.x2 + a.z2*b.x3 + a.w2*b.x4, /*|*/ a.x2*b.y1 + a.y2*b.y2 + a.z2*b.y3 + a.w2*b.y4, /*|*/ a.x2*b.z1 + a.y2*b.z2 + a.z2*b.z3 + a.w2*b.z4, /*|*/ a.x2*b.w1 + a.y2*b.w2 + a.z2*b.w3 + a.w2*b.w4,
        a.x3*b.x1 + a.y3*b.x2 + a.z3*b.x3 + a.w3*b.x4, /*|*/ a.x3*b.y1 + a.y3*b.y2 + a.z3*b.y3 + a.w3*b.y4, /*|*/ a.x3*b.z1 + a.y3*b.z2 + a.z3*b.z3 + a.w3*b.z4, /*|*/ a.x3*b.w1 + a.y3*b.w2 + a.z3*b.w3 + a.w3*b.w4,
        a.x4*b.x1 + a.y4*b.x2 + a.z4*b.x3 + a.w4*b.x4, /*|*/ a.x4*b.y1 + a.y4*b.y2 + a.z4*b.y3 + a.w4*b.y4, /*|*/ a.x4*b.z1 + a.y4*b.z2 + a.z4*b.z3 + a.w4*b.z4, /*|*/ a.x4*b.w1 + a.y4*b.w2 + a.z4*b.w3 + a.w4*b.w4
    };
    return mat;
}


static Matrix4F buildPerspectiveProjectionMatrix(float fieldOfViewY, float aspectRatio, float zNearPlane, float zFarPlane)
{
    // TODO check this:
    // assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
    Matrix4F mat;
      
    mat.x1 = 1.0F / ((tan(fieldOfViewY/2.0F)) * aspectRatio); mat.y1 = 0.0F;                             mat.z1 = 0.0F;                                                  mat.w1 = 0.0F;
    mat.x2 = 0.0F;                                            mat.y2 = 1.0F / (tan(fieldOfViewY/2.0F));  mat.z2 = 0.0F;                                                  mat.w2 = 0.0F;
    mat.x3 = 0.0F;                                            mat.y3 = 0.0F;                             mat.z3 = ( (zNearPlane + zFarPlane)/(zNearPlane - zFarPlane) ); mat.w3 = ( (2.0F * zNearPlane * zFarPlane)/(zNearPlane - zFarPlane) );
    mat.x4 = 0.0F;                                            mat.y4 = 0.0F;                             mat.z4 = -1;                                                    mat.w4 = 0.0F;
    
    return mat;
}

static Matrix4GLF buildPerspectiveProjectionMatrixGLF(float fieldOfViewY, float aspectRatio, float zNearPlane, float zFarPlane)
{
    // TODO check this:
    // assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
    Matrix4GLF mat;
      
    mat.x1 = static_cast<GLfloat>(1 / ((tan(fieldOfViewY/2.0F)) * aspectRatio)); mat.y1 = 0; mat.z1 = 0; mat.w1 = 0;
    mat.x2 = 0; mat.y2 = static_cast<GLfloat>(1 / (tan(fieldOfViewY/2))); mat.z2 = 0; mat.w2 = 0;
    mat.x3 = 0; mat.y3 = 0; mat.z3 = static_cast<GLfloat>( (zNearPlane + zFarPlane)/(zNearPlane - zFarPlane) ); mat.w3 = static_cast<GLfloat>( (2 * zNearPlane * zFarPlane)/(zNearPlane - zFarPlane) );
    mat.x4 = 0; mat.y4 = 0; mat.z4 = -1; mat.w4 = 0;
    
    return mat;
}

static Matrix4F buildTranslationMatrix(float x, float y, float z)
{
    Matrix4F mat;
      
    mat.x1 = 1.0F; mat.y1 = 0.0F; mat.z1 = 0.0F; mat.w1 = 0.0F;
    mat.x2 = 0.0F; mat.y2 = 1.0F; mat.z2 = 0.0F; mat.w2 = 0.0F;
    mat.x3 = 0.0F; mat.y3 = 0.0F; mat.z3 = 1.0F; mat.w3 = 0.0F;
    mat.x4 = x;    mat.y4 = y;    mat.z4 = z;    mat.w4 = 1.0F;
    
    return mat;
}

static Matrix4GLF buildTranslationMatrixGL(GLfloat x, GLfloat y, GLfloat z)
{
    Matrix4GLF mat;
      
    mat.x1 = 1.0F; mat.y1 = 0.0F; mat.z1 = 0.0F; mat.w1 = 0.0F;
    mat.x2 = 0.0F; mat.y2 = 1.0F; mat.z2 = 0.0F; mat.w2 = 0.0F;
    mat.x3 = 0.0F; mat.y3 = 0.0F; mat.z3 = 1.0F; mat.w3 = 0.0F;
    mat.x4 = x;    mat.y4 = y;    mat.z4 = z;    mat.w4 = 1.0F;
    
    return mat;
}


//Rotate X
static Matrix4F buildPitchMatrix(float rad) // Rotate around X axis
{
    Matrix4F mat;

    mat.x1 = 1.0F; mat.y1 = 0.0F;     mat.z1 = 0.0F;      mat.w1 = 0.0F;
    mat.x2 = 0.0F; mat.y2 = cos(rad); mat.z2 = -sin(rad); mat.w2 = 0.0F;
    mat.x3 = 0.0F; mat.y3 = sin(rad); mat.z3 = cos(rad);  mat.w3 = 0.0F;
    mat.x4 = 0.0F; mat.y4 = 0.0F;     mat.z4 = 0.0F;      mat.w4 = 1.0F;
        
    return mat;
}

//Rotate Y
static Matrix4F buildYawMatrix(float rad) // Rotate around Y axis
{
    Matrix4F mat;

    mat.x1 = cos(rad);  mat.y1 = 0.0F; mat.z1 = sin(rad); mat.w1 = 0.0F;
    mat.x2 = 0.0F;      mat.y2 = 1.0F; mat.z2 = 0.0F;     mat.w2 = 0.0F;
    mat.x3 = -sin(rad); mat.y3 = 0.0F; mat.z3 = cos(rad); mat.w3 = 0.0F;
    mat.x4 = 0.0F;      mat.y4 = 0.0F; mat.z4 = 0.0F;     mat.w4 = 1.0F;
        
    return mat;
}

//Rotate Z
static Matrix4F buildRollMatrix(float rad) // Rotate around Z axis
{
    Matrix4F mat;

    mat.x1 = cos(rad); mat.y1 = -sin(rad); mat.z1 = 0.0F; mat.w1 = 0.0F;
    mat.x2 = sin(rad); mat.y2 = cos(rad);  mat.z2 = 0.0F; mat.w2 = 0.0F;
    mat.x3 = 0.0F;     mat.y3 = 0.0F;      mat.z3 = 1.0F; mat.w3 = 0.0F;
    mat.x4 = 0.0F;     mat.y4 = 0.0F;      mat.z4 = 0.0F; mat.w4 = 1.0F;

    return mat;
}

static Matrix4F buildScaleMatrix(float x, float y, float z)
{
    Matrix4F mat;

    mat.x1 = x;    mat.y1 = 0.0F; mat.z1 = 0.0F; mat.w1 = 0.0F;
    mat.x2 = 0.0F; mat.y2 = y;    mat.z2 = 0.0F; mat.w2 = 0.0F;
    mat.x3 = 0.0F; mat.y3 = 0.0F; mat.z3 = z;    mat.w3 = 0.0F;
    mat.x4 = 0.0F; mat.y4 = 0.0F; mat.z4 = 0.0F; mat.w4 = 1.0F;

    return mat;
}

//}

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
