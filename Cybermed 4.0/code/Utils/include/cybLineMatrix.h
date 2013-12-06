#ifndef CYBLINEMATRIX_H_INCLUDED
#define CYBLINEMATRIX_H_INCLUDED

#include <cmath>
#include <cstring>
#include <iostream>
#include "cybVector.h"

using namespace std;

typedef float mat2[4];
typedef int imat2[4];
typedef float mat3[9];  //Colum-first float 3x3 matrix, GL-style.
typedef int imat3[9];   //Colum-first integer 3x3 matrix, GL-style.
typedef float mat4[16]; //Colum-first float 4x4 matrix, GL-style.
typedef int imat4[16];  //Colum-first integer 4x4 matrix, GL-style.

class CybLineMatrix
{
    public:
	static void copyMatrix2D(const mat2 src, mat2 dest);
        static void copyMatrix2D(const imat2 src, imat2 dest);
        static void copyMatrix3D(const mat3 src, mat3 dest);
        static void copyMatrix3D(const imat3 src, imat3 dest);
        static void copyMatrix4D(const mat4 src, mat4 dest);
        static void copyMatrix4D(const imat4 src, imat4 dest);

	static void createCofactorMatrix3D(mat3 m, mat3 cofMat);

        static void createFrustum(mat4 frustum, float left, float right, float bottom,
                                                      float top, float zNear, float zFar);

	static void createNormalMatrix(mat4 modelview, mat3 nm);	

        static void createOrthographicMatrix(mat4 orto, float left, float right, float bottom,
                                             float top, float zNear, float zFar);

        static void createPerspectiveMatrix(mat4 persp, float fovy, float aspect,
                                                     float zNear, float zFar);

        static void createRotationMatrix3D(mat3 rm, float angle, float x, float y, float z);
        static void createRotationMatrix4D(mat4 rm, float angle, float x, float y, float z);

        static void createScaleMatrix3D(mat3 sm, float x, float y, float z);
        static void createScaleMatrix4D(mat4 sm, float x, float y, float z);

        static void createTranslationMatrix4D(mat4 tm, float x, float y, float z);

	static float determinant2D(mat2 m);	
	static float determinant3D(mat3 m);

        static void getColumn3D(mat3 m, float* col, int numCol);
        static void getColumn3D(imat3 m, int* col, int numCol);
        static void getColumn4D(mat4 m, float* col, int numCol);
        static void getColumn4D(imat4 m, int* col, int numCol);

	static float getDistanceToPlane(vec4 plane, vec3 point);
	static void getPlaneEquation(vec3 p1, vec3 p2, vec3 p3, vec4 plane);

	static void invertMatrix3D(mat3 mi, mat3 mf);
        static void invertMatrix4D(mat4 mi, mat4 mf);

        static void loadIdentity3D(mat3 m);
        static void loadIdentity4D(mat4 m);
        static void loadIdentity3D(imat3 m);
        static void loadIdentity4D(imat4 m);

        static void multiplyMatrices3D(const mat3 m1, const mat3 m2, mat3 res);
        static void multiplyMatrices3D(const imat3 m1, const imat3 m2, imat3 res);
        static void multiplyMatrices4D(const mat4 m1, const mat4 m2, mat4 res);
        static void multiplyMatrices4D(const imat4 m1, const imat4 m2, imat4 res);

        static void rotate(mat3 rm, const float* vi, float* vf);

	static void scalarMultiplication2D(mat2 m, float s);
	static void scalarMultiplication3D(mat3 m, float s);
	static void scalarMultiplication4D(mat4 m, float s);

        static void setColumn3D(mat3 m, float* col, int numCol);
        static void setColumn3D(imat3 m, int* col, int numCol);
        static void setColumn4D(mat4 m, float* col, int numCol);
        static void setColumn4D(imat4 m, int* col, int numCol);

        static void transform3D(mat4 mt, const float* vi, float* vf);
        static void transform4D(mat4 mt, const float* vi, float* vf);

	static void transposeMatrix2D(mat2 orig, mat2 transp);
	static void transposeMatrix3D(mat2 orig, mat2 transp);
	static void transposeMatrix4D(mat4 orig, mat4 transp);

    private:
        static double detIJ(const mat4 m, const int i, const int j);

};



#endif // CYBLINEMATRIX_H_INCLUDED
