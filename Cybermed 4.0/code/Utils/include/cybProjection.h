#ifndef CYBPROJECTION_H_INCLUDED
#define CYBPROJECTION_H_INCLUDED

#include "cybFrame.h"

class CybProjection
{
    public:
        CybProjection();
        virtual const mat4& getProjectionMatrix();
        void transformCorners(CybFrame& cam);
        bool isInsideFrustum(float x, float y, float z, float radius);
        bool isInsideFrustum(vec3 p, float radius);
    protected:
        //The projection matrix.
        mat4 proj;

        //Frustum corners: we use the following convention:
        // l = left     r = right
        // b = bottom   t = top
        // n = near     f = far
        //We combine 3 of these letters to indicate which corner it is.
        vec4 ltn, lbn, rtn, rbn, ltf, lbf, rtf, rbf;

        //Transformed corners
        vec4 ltnTransf, lbnTransf, rtnTransf, rbnTransf,
                    ltfTransf, lbfTransf, rtfTransf, rbfTransf;

        //Plane equations
        vec4 lPlane, rPlane, bPlane, tPlane, nPlane, fPlane;
};

#endif // CYBPROJECTION_H_INCLUDED
