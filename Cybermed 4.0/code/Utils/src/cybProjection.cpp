#include "cybProjection.h"

#ifndef FOR
#define FOR(n) for(int i = 0; i < n; ++i)
#endif

CybProjection::CybProjection()
{
    CybLineMatrix::createOrthographicMatrix(proj, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    proj[15] = 1.0f;
    ltn[0] = -1.0f; ltn[1] =  1.0f; ltn[2] = -1.0f; ltn[3] = 1.0f;
    lbn[0] = -1.0f; lbn[1] = -1.0f; ltn[2] = -1.0f; ltn[3] = 1.0f;
    rtn[0] =  1.0f; rtn[1] =  1.0f; rtn[2] = -1.0f; rtn[3] = 1.0f;
    rbn[0] =  1.0f; rbn[1] = -1.0f; rtn[2] = -1.0f; rtn[3] = 1.0f;
    ltf[0] = -1.0f; ltf[1] =  1.0f; ltf[2] =  1.0f; ltf[3] = 1.0f;
    lbf[0] = -1.0f; lbf[1] = -1.0f; ltf[2] =  1.0f; ltf[3] = 1.0f;
    rtf[0] =  1.0f; rtf[1] =  1.0f; rtf[2] =  1.0f; rtf[3] = 1.0f;
    rbf[0] =  1.0f; rbf[1] = -1.0f; rtf[2] =  1.0f; rtf[3] = 1.0f;
}

const mat4& CybProjection::getProjectionMatrix()
{
    return proj;
}

void CybProjection::transformCorners(CybFrame& cam)
{
    mat4 rotMat;
    vec3 forward, up, x, origin;

    cam.getForward(forward);
    FOR(3) forward[i] = -forward[i];
    cam.getOrigin(origin);
    cam.getUp(up);
    x[0] = up[1] * forward[2] - up[2] * forward[1];
    x[1] = up[2] * forward[0] - up[0] * forward[2];
    x[2] = up[0] * forward[1] - up[1] * forward[0];

    //Assembling the matrix
    memcpy(rotMat, x, sizeof(float) * 3);
    rotMat[3] = 0.0f;
    memcpy(&rotMat[4], up, sizeof(float) * 3);
    rotMat[7] = 0.0f;
    memcpy(&rotMat[8], forward, sizeof(float) * 3);
    rotMat[11] = 0.0f;
    memcpy(&rotMat[12], origin, sizeof(float) * 3);
    rotMat[15] = 1.0f;

    //Transforming the corners
    CybLineMatrix::transform4D(rotMat, ltn, ltnTransf);
    CybLineMatrix::transform4D(rotMat, lbn, lbnTransf);
    CybLineMatrix::transform4D(rotMat, rtn, rtnTransf);
    CybLineMatrix::transform4D(rotMat, rbn, rbnTransf);
    CybLineMatrix::transform4D(rotMat, ltf, ltfTransf);
    CybLineMatrix::transform4D(rotMat, lbf, lbfTransf);
    CybLineMatrix::transform4D(rotMat, rtf, rtfTransf);
    CybLineMatrix::transform4D(rotMat, rbf, rbfTransf);

    //Calculating plane equations
    // Near and Far Planes
    CybLineMatrix::getPlaneEquation(ltnTransf, lbnTransf, rbnTransf, nPlane);
    CybLineMatrix::getPlaneEquation(ltfTransf, rtfTransf, rbfTransf, fPlane);
            
    // Top and Bottom Planes
    CybLineMatrix::getPlaneEquation(ltnTransf, rtnTransf, rtfTransf, tPlane);
    CybLineMatrix::getPlaneEquation(lbnTransf, lbfTransf, rbfTransf, bPlane);

    // Left and right planes
    CybLineMatrix::getPlaneEquation(lbnTransf, ltnTransf, ltfTransf, lPlane);
    CybLineMatrix::getPlaneEquation(rbnTransf, rbfTransf, rtfTransf, rPlane);
}

bool CybProjection::isInsideFrustum(float x, float y, float z, float radius)
{
    vec3 p;
    p[0] = x; p[1] = y; p[2] = z;
    return isInsideFrustum(p, radius);
}

bool CybProjection::isInsideFrustum(vec3 p, float radius)
{
	float dist;
	dist = CybLineMatrix::getDistanceToPlane(nPlane, p);
	if(dist + radius  <= 0.0) return false;

	dist = CybLineMatrix::getDistanceToPlane(fPlane, p);
	if(dist + radius  <= 0.0) return false;

	dist = CybLineMatrix::getDistanceToPlane(lPlane, p);
	if(dist + radius  <= 0.0) return false;

	dist = CybLineMatrix::getDistanceToPlane(rPlane, p);
	if(dist + radius  <= 0.0) return false;

	dist = CybLineMatrix::getDistanceToPlane(bPlane, p);
	if(dist + radius  <= 0.0) return false;
	
	dist = CybLineMatrix::getDistanceToPlane(tPlane, p);
	if(dist + radius  <= 0.0) return false;

	return true;
}
