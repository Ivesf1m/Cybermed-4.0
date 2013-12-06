#ifndef CYBPERSPECTIVEPROJECTION_H_INCLUDED
#define CYBPERSPECTIVEPROJECTION_H_INCLUDED

#define PI 3.141592

#include "cybProjection.h"

class CybPerspectiveProjection : public CybProjection
{
    public:
        CybPerspectiveProjection(float left, float right, float bottom,
                                 float top, float zNear, float zFar);
        CybPerspectiveProjection(float fovy, float aspect, float zNear, float zFar);
        void setPerspectiveProjection(float left, float right, float bottom,
                                      float top, float zNear, float zFar);
        void setPerspectiveProjection(float fovy, float aspect, float zNear, float zFar);
};

#endif // CYBPERSPECTIVEPROJECTION_H_INCLUDED
