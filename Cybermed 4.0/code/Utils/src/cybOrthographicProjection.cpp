#include "cybOrthographicProjection.h"

CybOrthographicProjection::CybOrthographicProjection(float left, float right, float bottom,
                                                     float top, float zNear, float zFar)
{
    this->setOrthographicProjection(left, right, bottom, top, zNear, zFar);
}

void CybOrthographicProjection::setOrthographicProjection(float left, float right, float bottom,
                                                          float top, float zNear, float zFar)
{
    CybLineMatrix::createOrthographicMatrix(proj, left, right, bottom, top, zNear, zFar);
    proj[15] = 1.0f;
    ltn[0] =  left; ltn[1] =    top; ltn[2] = zNear; ltn[3] = 1.0f;
    lbn[0] =  left; lbn[1] = bottom; ltn[2] = zNear; ltn[3] = 1.0f;
    rtn[0] = right; rtn[1] =    top; rtn[2] = zNear; rtn[3] = 1.0f;
    rbn[0] = right; rbn[1] = bottom; rtn[2] = zNear; rtn[3] = 1.0f;
    ltf[0] =  left; ltf[1] =    top; ltf[2] =  zFar; ltf[3] = 1.0f;
    lbf[0] =  left; lbf[1] = bottom; ltf[2] =  zFar; ltf[3] = 1.0f;
    rtf[0] = right; rtf[1] =    top; rtf[2] =  zFar; rtf[3] = 1.0f;
    rbf[0] = right; rbf[1] = bottom; rtf[2] =  zFar; rtf[3] = 1.0f;
}
