#include "cybPerspectiveProjection.h"

CybPerspectiveProjection::CybPerspectiveProjection(float left, float right, float bottom,
                                                   float top, float zNear, float zFar)
{
    this->setPerspectiveProjection(left, right, bottom, top, zNear, zFar);
}

CybPerspectiveProjection::CybPerspectiveProjection(float fovy, float aspect, float zNear, float zFar)
{
    this->setPerspectiveProjection(fovy, aspect, zNear, zFar);
}

void CybPerspectiveProjection::setPerspectiveProjection(float left, float right, float bottom,
                                                        float top, float zNear, float zFar)
{
    CybLineMatrix::createFrustum(proj, left, right, bottom, top, zNear, zFar);
    float fovy = (360 / PI) * atan(top/zNear);
    float asp = left / bottom;
    float topF = zFar * tanf(fovy * (PI/360));
    float bottomF = -topF;
    float leftF = bottomF * asp;
    float rightF = -leftF;

    //Setting corners
    ltn[0] =   left; ltn[1] =     top; ltn[2] = zNear; ltn[3] = 1.0f;
    lbn[0] =   left; lbn[1] =  bottom; ltn[2] = zNear; ltn[3] = 1.0f;
    rtn[0] =  right; rtn[1] =     top; rtn[2] = zNear; rtn[3] = 1.0f;
    rbn[0] =  right; rbn[1] =  bottom; rtn[2] = zNear; rtn[3] = 1.0f;
    ltf[0] =  leftF; ltf[1] =    topF; ltf[2] =  zFar; ltf[3] = 1.0f;
    lbf[0] =  leftF; lbf[1] = bottomF; ltf[2] =  zFar; ltf[3] = 1.0f;
    rtf[0] = rightF; rtf[1] =    topF; rtf[2] =  zFar; rtf[3] = 1.0f;
    rbf[0] = rightF; rbf[1] = bottomF; rtf[2] =  zFar; rtf[3] = 1.0f;
}

void CybPerspectiveProjection::setPerspectiveProjection(float fovy, float aspect, float zNear, float zFar)
{
    CybLineMatrix::loadIdentity4D(proj);
    float top = zNear * tanf(fovy * 0.5f);
    float bottom = -top;
    float left = bottom * aspect;
    float right = -left;
    this->setPerspectiveProjection(left, right, bottom, top, zNear, zFar);
}
