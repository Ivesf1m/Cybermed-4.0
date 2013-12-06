#ifndef CYBFRAME_H_INCLUDED
#define CYBFRAME_H_INCLUDED

#include "cybLineMatrix.h"
#include "cybVector.h"
#include <cstring>
#include <cmath>

using namespace std;

class CybFrame
{
    public:
        CybFrame();
        void getCameraMatrix(mat4 cm, bool rotOnly = false);
        void getForward(vec3 f);
        void getFrameMatrix(mat4 m, bool rotOnly = false);
        void getOrigin(vec3 o);
        float getOriginX();
        float getOriginY();
        float getOriginZ();
        void getUp(vec3 u);
        void getXAxis(vec3 x);
        void getYAxis(vec3 y);
        void getZAxis(vec3 z);
        void localRotation(float angle, float x, float y, float z);
        void localToWorld(const vec3 local, vec3 world, bool rotOnly = false);
        void localTranslation(float x, float y, float z);
        void moveForward(float delta);
        void moveRight(float delta);
        void moveUp(float delta);
        void normalizeBasis();
        void rotateLocalX(float angle);
        void rotateLocalY(float angle);
        void rotateLocalZ(float angle);
        void rotateVector(const vec3 pi, vec3 pf);
        void setForward(const vec3 point);
        void setForward(float x, float y, float z);
        void setOrigin(const vec3 point);
        void setOrigin(float x, float y, float z);
        void setUp(const vec3 point);
        void setUp(float x, float y, float z);
        void transformPoint(const vec3 pi, vec3 pf);
        void worldRotation(float angle, float x, float y, float z);
        void worldToLocal(const vec3 world, vec3 local);
        void worldTranslation(float x, float y, float z);

    private:
        vec3 up;
        vec3 forward;
        vec3 origin;
};

#endif // CYBFRAME_H_INCLUDED
