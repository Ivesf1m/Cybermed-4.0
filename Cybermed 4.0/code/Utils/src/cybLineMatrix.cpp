#include "cybLineMatrix.h"

#define FOR(n) for(int i = 0; i < n; ++i)

void CybLineMatrix::copyMatrix2D(const mat2 src, mat2 dest)
{
    memcpy(dest, src, sizeof(mat2));
}

void CybLineMatrix::copyMatrix2D(const imat2 src, imat2 dest)
{
    memcpy(dest, src, sizeof(mat2));
}

void CybLineMatrix::copyMatrix3D(const mat3 src, mat3 dest)
{
    memcpy(dest, src, sizeof(mat3));
}

void CybLineMatrix::copyMatrix3D(const imat3 src, imat3 dest)
{
    memcpy(dest, src, sizeof(imat3));
}

void CybLineMatrix::copyMatrix4D(const mat4 src, mat4 dest)
{
    memcpy(dest, src, sizeof(mat4));
}

void CybLineMatrix::copyMatrix4D(const imat4 src, imat4 dest)
{
    memcpy(dest, src, sizeof(imat4));
}

void CybLineMatrix::createCofactorMatrix3D(mat3 m, mat3 cofMat)
{
	mat2 m11, m12, m13, m21, m22, m23, m31, m32, m33;
	float detm11, detm12, detm13, detm21, detm22, detm23, detm31, detm32, detm33;

	//Splitting the matrix m in all 2x2 possible matrices.
	m11[0] = m[4]; m11[1] = m[5]; m11[2] = m[7]; m11[3] = m[8];
	m12[0] = m[1]; m12[1] = m[2]; m12[2] = m[7]; m12[3] = m[8];
	m13[0] = m[1]; m13[1] = m[2]; m13[2] = m[4]; m13[3] = m[5];
	m21[0] = m[3]; m21[1] = m[5]; m21[2] = m[6]; m21[3] = m[8];
	m22[0] = m[0]; m22[1] = m[2]; m22[2] = m[6]; m22[3] = m[8];
	m23[0] = m[0]; m23[1] = m[2]; m23[2] = m[3]; m23[3] = m[5];
	m31[0] = m[3]; m31[1] = m[4]; m31[2] = m[6]; m31[3] = m[7];
	m32[0] = m[4]; m32[1] = m[5]; m32[2] = m[7]; m32[3] = m[8];
	m33[0] = m[0]; m33[1] = m[1]; m33[2] = m[3]; m33[3] = m[4];

	//Calculating the determinant of the matrices.
	detm11 = CybLineMatrix::determinant2D(m11);
	detm12 = CybLineMatrix::determinant2D(m12);
	detm13 = CybLineMatrix::determinant2D(m13);
	detm21 = CybLineMatrix::determinant2D(m21);
	detm22 = CybLineMatrix::determinant2D(m22);
	detm23 = CybLineMatrix::determinant2D(m23);
	detm31 = CybLineMatrix::determinant2D(m31);
	detm32 = CybLineMatrix::determinant2D(m32);
	detm33 = CybLineMatrix::determinant2D(m33);
	
	//Filling in the cofactor matrix
	cofMat[0] = detm11;
	cofMat[1] = -detm21;
	cofMat[2] = detm31;
	cofMat[3] = -detm12;
	cofMat[4] = detm22;
	cofMat[5] = -detm32;
	cofMat[6] = detm13;
	cofMat[7] = -detm23;
	cofMat[8] = detm33;

	FOR(9) cout << cofMat[i] << "     ";
	cout << endl;
}

void CybLineMatrix::createFrustum(mat4 frustum, float left, float right, float bottom,
                                  float top, float zNear, float zFar)
{
    CybLineMatrix::loadIdentity4D(frustum);
    frustum[0] = (2.0f * zNear) / (right - left);
    frustum[5] = (2.0f * zNear) / (top - bottom);
    frustum[8] = (right + left) / (right - left);
    frustum[9] = (top * bottom) / (top - bottom);
    frustum[10] = -((zFar + zNear) / (zFar - zNear));
    frustum[11] = -1.0f;
    frustum[14] = -((2.0f * zFar * zNear) / (zFar - zNear));
    frustum[15] = 0.0f;
}

void CybLineMatrix::createNormalMatrix(mat4 modelview, mat3 nm)
{
	nm[0] = modelview[0]; nm[1] = modelview[1]; nm[2] = modelview[2];
	nm[3] = modelview[4]; nm[4] = modelview[5]; nm[5] = modelview[6];
	nm[6] = modelview[8]; nm[7] = modelview[9]; nm[8] = modelview[10];
	mat3 aux;
	CybLineMatrix::invertMatrix3D(nm, aux);
	CybLineMatrix::transposeMatrix3D(aux, nm);
}

void CybLineMatrix::createOrthographicMatrix(mat4 orto, float left, float right, float bottom,
                                             float top, float zNear, float zFar)
{
    CybLineMatrix::loadIdentity4D(orto);
    orto[0] = 2.0f / (right - left);
    orto[5] = 2.0f / (top - bottom);
    orto[10] = -2.0f / (zFar - zNear);
    orto[12] = -( (right + left) / (right - left) );
    orto[13] = -( (top + bottom) / (top - bottom) );
    orto[14] = -( (zFar + zNear) / (zFar - zNear) );
    orto[15] = 1.0f;
}

void CybLineMatrix::createRotationMatrix3D(mat3 rm, float angle, float x, float y, float z)
{
    float norma, seno, cosseno;
    seno = sin(angle);
    cosseno = cos(angle);
    norma = sqrt(x*x + y*y + z*z);
    if(!norma)
    {
        CybLineMatrix::loadIdentity3D(rm);
        return;
    }
    x /= norma; y /= norma; z /= norma;
    float comp = 1.0f - cosseno;
    rm[0] = (comp * x * x ) + cosseno;
    rm[1] = (comp * x * y ) - (z * seno);
    rm[2] = (comp * x * z ) + (y * seno);
    rm[3] = (comp * x * y ) + (z * seno);
    rm[4] = (comp * y * y ) + cosseno;
    rm[5] = (comp * y * z ) - (x * seno);
    rm[6] = (comp * x * z ) - (y * seno);
    rm[7] = (comp * y * z ) + (x * seno);
    rm[8] = (comp * z * z ) + cosseno;
}

void CybLineMatrix::createRotationMatrix4D(mat4 rm, float angle, float x, float y, float z)
{
    float norma, seno, cosseno;
    seno = sin(angle);
    cosseno = cos(angle);
    norma = sqrt(x*x + y*y + z*z);
    if(!norma)
    {
        CybLineMatrix::loadIdentity3D(rm);
        return;
    }
    x /= norma; y /= norma; z /= norma;
    float comp = 1.0f - cosseno;
    rm[0] = (comp * x * x ) + cosseno;
    rm[1] = (comp * x * y ) - (z * seno);
    rm[2] = (comp * x * z ) + (y * seno);
    rm[3] = 0.0f;
    rm[4] = (comp * x * y ) + (z * seno);
    rm[5] = (comp * y * y ) + cosseno;
    rm[6] = (comp * y * z ) - (x * seno);
    rm[7] = 0.0f;
    rm[8] = (comp * x * z ) - (y * seno);
    rm[9] = (comp * y * z ) + (x * seno);
    rm[10] = (comp * z * z ) + cosseno;
    rm[11] = rm[12] = rm[13] = rm[14] = 0.0f;
    rm[15] = 1.0f;
}

void CybLineMatrix::createScaleMatrix3D(mat3 sm, float x, float y, float z)
{
    CybLineMatrix::loadIdentity3D(sm);
    sm[0] = x;
    sm[4] = y;
    sm[8] = z;
}
void CybLineMatrix::createScaleMatrix4D(mat4 sm, float x, float y, float z)
{
    CybLineMatrix::loadIdentity4D(sm);
    sm[0] = x;
    sm[5] = y;
    sm[10] = z;
}

void CybLineMatrix::createPerspectiveMatrix(mat4 persp, float fovy, float aspect,
                                                     float zNear, float zFar)
{
    CybLineMatrix::loadIdentity4D(persp);
    float top = zNear * tanf(fovy * 0.5f);
    float bottom = -top;
    float left = bottom * aspect;
    float right = -left;
    CybLineMatrix::createFrustum(persp, left, right, bottom, top, zNear, zFar);
}

void CybLineMatrix::createTranslationMatrix4D(mat4 tm, float x, float y, float z)
{
    CybLineMatrix::loadIdentity4D(tm);
    tm[12] = x;
    tm[13] = y;
    tm[14] = z;
}

float CybLineMatrix::determinant2D(mat2 m)
{
	float det = 0;
	det = m[0] * m[3] - m[1] * m[2];
	return det;
}

float CybLineMatrix::determinant3D(mat3 m)
{
	float det = 0;
	det += m[0] * m[4] * m[8];
	det += m[3] * m[7] * m[2];
	det += m[6] * m[1] * m[5];
	det -= m[6] * m[4] * m[2];
	det -= m[3] * m[1] * m[8];
	det -= m[0] * m[7] * m[5];
	return det; 
}

double CybLineMatrix::detIJ(const mat4 m, const int i, const int j)
{
    int x = 0, y, ii, jj;
    double ret, mat[3][3];
    for(ii = 0; ii < 4; ++ii)
    {
        if(ii == i) continue;
        y = 0;
        for(jj = 0; jj < 4; ++jj)
        {
            if(jj == j) continue;
            mat[x][y] = m[(ii*4) + jj];
            ++y;
        }
        ++x;
    }
    ret =  mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
    ret -= mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    ret += mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
    return ret;
}

void CybLineMatrix::getColumn3D(mat3 m, float* col, int numCol)
{
    memcpy(col, m + (3 * numCol), sizeof(float) * 3);
}

void CybLineMatrix::getColumn3D(imat3 m, int* col, int numCol)
{
    memcpy(col, m + (3 * numCol), sizeof(int) * 3);
}

void CybLineMatrix::getColumn4D(mat4 m, float* col, int numCol)
{
    memcpy(col, m + (4 * numCol), sizeof(float) * 4);
}

void CybLineMatrix::getColumn4D(imat4 m, int* col, int numCol)
{
    memcpy(col, m + (4 * numCol), sizeof(int) * 4);
}

float CybLineMatrix::getDistanceToPlane(vec4 plane, vec3 point)
{
	return (plane[0] * point[0] + plane[1] * point[1] + plane[2] * point[2] + plane[3]); 
}

void CybLineMatrix::getPlaneEquation(vec3 p1, vec3 p2, vec3 p3, vec4 plane)
{
	vec3 v1, v2;
	FOR(3){
		v2[i] = p2[i] - p1[i];
		v1[i] = p3[i] - p1[i];
	}

	plane[0] = v1[1] * v2[2] - v2[1] * v1[2];
	plane[1] = v2[0] * v1[2] - v1[0] * v2[2];
	plane[2] = v1[0] * v2[1] - v1[1] * v2[0];
	float norma = 0;
	FOR(3) norma += plane[i] * plane[i];
	norma = sqrt(norma);
	FOR(3) plane[i] /= norma;
	plane[3] = -(plane[0] * p3[0] + plane[1] * p3[1] + plane[2] * p3[2]);
}

void CybLineMatrix::invertMatrix3D(mat3 mi, mat3 mf)
{
	float det = CybLineMatrix::determinant3D(mi);
	cout << det << endl;
	CybLineMatrix::createCofactorMatrix3D(mi, mf);
	CybLineMatrix::scalarMultiplication3D(mf, 1.0f/det);	
}

void CybLineMatrix::invertMatrix4D(mat4 mi, mat4 mf)
{
    int i, j;
    float det = 0.0f, detij;
    for(i = 0; i < 4; ++i)
    {
        det += (i & 0x1) ? (-mi[i] * detIJ(mi, 0, i)) : (mi[i] * detIJ(mi, 0, i));
    }
    det = 1.0f / det;
    for(i = 0; i < 4; ++i)
    {
        for(j = 0; j < 4; ++j)
        {
            detij = detIJ(mi, j, i);
            mf[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij * det);
        }
    }
}

void CybLineMatrix::loadIdentity3D(mat3 m)
{
    static mat3 id = {1.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 1.0f};
    CybLineMatrix::copyMatrix3D(id, m);
}

void CybLineMatrix::loadIdentity4D(mat4 m)
{
    static mat4 id = {1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f};
    CybLineMatrix::copyMatrix4D(id, m);
}

void CybLineMatrix::loadIdentity3D(imat3 m)
{
    static imat3 id = {1, 0, 0,
                       0, 1, 0,
                       0, 0, 1};
    CybLineMatrix::copyMatrix3D(id, m);
}

void CybLineMatrix::loadIdentity4D(imat4 m)
{
    static imat4 id = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1};
    CybLineMatrix::copyMatrix4D(id, m);
}

#define m(r, c) m1[(c * 3) + r]
#define n(r, c) m2[(c * 3) + r]
#define p(r, c) res[(c * 3) + r]
void CybLineMatrix::multiplyMatrices3D(const mat3 m1, const mat3 m2, mat3 res)
{
    FOR(3)
    {
        float m1i0 = m(i, 0), m1i1 = m(i, 1), m1i2 = m(i, 2);
        p(i, 0) = m1i0 * n(0, 0) + m1i1 * n(1, 0) + m1i2 * n(2, 0);
        p(i, 1) = m1i0 * n(0, 1) + m1i1 * n(1, 1) + m1i2 * n(2, 1);
        p(i, 2) = m1i0 * n(0, 2) + m1i1 * n(1, 2) + m1i2 * n(2, 2);
    }
}

void CybLineMatrix::multiplyMatrices3D(const imat3 m1, const imat3 m2, imat3 res)
{
    FOR(3)
    {
        float m1i0 = m(i, 0), m1i1 = m(i, 1), m1i2 = m(i, 2);
        p(i, 0) = m1i0 * n(0, 0) + m1i1 * n(1, 0) + m1i2 * n(2, 0);
        p(i, 1) = m1i0 * n(0, 1) + m1i1 * n(1, 1) + m1i2 * n(2, 1);
        p(i, 2) = m1i0 * n(0, 2) + m1i1 * n(1, 2) + m1i2 * n(2, 2);
    }
}

#undef m
#undef n
#undef p

#define m(r, c) m1[(c * 4) + r]
#define n(r, c) m2[(c * 4) + r]
#define p(r, c) res[(c * 4) + r]
void CybLineMatrix::multiplyMatrices4D(const mat4 m1, const mat4 m2, mat4 res)
{
    FOR(4)
    {
        float m1i0 = m(i, 0), m1i1 = m(i, 1), m1i2 = m(i, 2), m1i3 = m(i, 3);
        p(i, 0) = m1i0 * n(0, 0) + m1i1 * n(1, 0) + m1i2 * n(2, 0) + m1i3 * n(3, 0);
        p(i, 1) = m1i0 * n(0, 1) + m1i1 * n(1, 1) + m1i2 * n(2, 1) + m1i3 * n(3, 1);
        p(i, 2) = m1i0 * n(0, 2) + m1i1 * n(1, 2) + m1i2 * n(2, 2) + m1i3 * n(3, 2);
        p(i, 3) = m1i0 * n(0, 3) + m1i1 * n(1, 3) + m1i2 * n(2, 3) + m1i3 * n(3, 3);
    }
}

void CybLineMatrix::multiplyMatrices4D(const imat4 m1, const imat4 m2, imat4 res)
{
    FOR(4)
    {
        float m1i0 = m(i, 0), m1i1 = m(i, 1), m1i2 = m(i, 2), m1i3 = m(i, 3);
        p(i, 0) = m1i0 * n(0, 0) + m1i1 * n(1, 0) + m1i2 * n(2, 0) + m1i3 * n(3, 0);
        p(i, 1) = m1i0 * n(0, 1) + m1i1 * n(1, 1) + m1i2 * n(2, 1) + m1i3 * n(3, 1);
        p(i, 2) = m1i0 * n(0, 2) + m1i1 * n(1, 2) + m1i2 * n(2, 2) + m1i3 * n(3, 2);
        p(i, 3) = m1i0 * n(0, 3) + m1i1 * n(1, 3) + m1i2 * n(2, 3) + m1i3 * n(3, 3);
    }
}

#undef m
#undef n
#undef p

void CybLineMatrix::rotate(mat3 rm, const float* vi, float* vf)
{
    vf[0] = rm[0] * vi[0] + rm[3] * vi[1] + rm[6] * vi[2];
    vf[1] = rm[1] * vi[0] + rm[4] * vi[1] + rm[7] * vi[2];
    vf[2] = rm[2] * vi[0] + rm[5] * vi[1] + rm[8] * vi[2];
}

void CybLineMatrix::scalarMultiplication2D(mat2 m, float s)
{
	FOR(4) m[i] *= s;
}

void CybLineMatrix::scalarMultiplication3D(mat3 m, float s)
{
	FOR(9) m[i] *= s;
}

void CybLineMatrix::scalarMultiplication4D(mat4 m, float s)
{
	FOR(16) m[i] *= s;
}

void CybLineMatrix::setColumn3D(mat3 m, float* col, int numCol)
{
    memcpy(m + (3 * numCol), col, sizeof(float) * 3);
}

void CybLineMatrix::setColumn3D(imat3 m, int* col, int numCol)
{
    memcpy(m + (3 * numCol), col, sizeof(int) * 3);
}

 void CybLineMatrix::setColumn4D(mat4 m, float* col, int numCol)
 {
     memcpy(m + (4 * numCol), col, sizeof(float) * 4);
 }

 void CybLineMatrix::setColumn4D(imat4 m, int* col, int numCol)
 {
     memcpy(m + (4 * numCol), col, sizeof(int) * 4);
 }

 void CybLineMatrix::transform3D(mat4 mt, const float* vi, float* vf)
 {
     vf[0] = mt[0] * vi[0] + mt[4] * vi[1] + mt[8] * vi[2] + mt[12];
     vf[1] = mt[1] * vi[0] + mt[5] * vi[1] + mt[9] * vi[2] + mt[13];
     vf[2] = mt[2] * vi[0] + mt[6] * vi[1] + mt[10] * vi[2] + mt[14];
 }

 void CybLineMatrix::transform4D(mat4 mt, const float* vi, float* vf)
 {
     vf[0] = mt[0] * vi[0] + mt[4] * vi[1] + mt[8] * vi[2] + mt[12] * vi[3];
     vf[1] = mt[1] * vi[0] + mt[5] * vi[1] + mt[9] * vi[2] + mt[13] * vi[3];
     vf[2] = mt[2] * vi[0] + mt[6] * vi[1] + mt[10] * vi[2] + mt[14] * vi[3];
     vf[3] = mt[3] * vi[0] + mt[7] * vi[1] + mt[11] * vi[2] + mt[15] * vi[3];
 }

void CybLineMatrix::transposeMatrix2D(mat2 orig, mat2 transp)
{
	float swap;
	CybLineMatrix::copyMatrix2D(orig, transp);
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < i; ++j){
			swap = transp[i + j*2];
			transp[i + j*2] = transp[j + i*2];
			transp[j + i*2] = transp[i + j*2];
		}
	}
}
	
void CybLineMatrix::transposeMatrix3D(mat3 orig, mat3 transp)
{
	float swap;
	CybLineMatrix::copyMatrix3D(orig, transp);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < i; ++j){
			swap = transp[i + j*3];
			transp[i + j*3] = transp[j + i*3];
			transp[j + i*3] = transp[i + j*3];
		}
	}
}

void CybLineMatrix::transposeMatrix4D(mat4 orig, mat4 transp)
{
	float swap;
	CybLineMatrix::copyMatrix4D(orig, transp);
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < i; ++j){
			swap = transp[i + j*4];
			transp[i + j*4] = transp[j + i*4];
			transp[j + i*4] = transp[i + j*4];
		}
	}
}

int main()
{
    mat3 m = {1, 0, 5, 2, 1, 6, 3, 4, 0};
    mat3 mi;
    CybLineMatrix::invertMatrix3D(m, mi);
    FOR(9) cout << mi[i] << "    ";
    cout << endl;
    return 0;
}

#undef FOR
