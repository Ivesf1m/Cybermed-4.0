#ifndef CYBORTHOGRAPHICPROJECTION_H_INCLUDED
#define CYBORTHOGRAPHICPROJECTION_H_INCLUDED

#include "cybProjection.h"

class CybOrthographicProjection : public CybProjection
{
    public:
            CybOrthographicProjection(float left, float right, float bottom,
                                      float top, float zNear, float zFar);
            void setOrthographicProjection(float left, float right, float bottom,
                                           float top, float zNear, float zFar);
};


#endif // CYBORTHOGRAPHICPROJECTION_H_INCLUDED
