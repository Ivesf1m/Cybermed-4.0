#ifndef CYBMATRIXSTACK_H_INCLUDED
#define CYBMATRIXSTACK_H_INCLUDED

#include "cybLineMatrix.h"
#include "cybFrame.h"

class CybMatrixStack
{
    public:
        CybMatrixStack(int depth = 32);
        ~CybMatrixStack();
        mat4& getMatrix();
        void getMatrix(mat4 m);
        void loadIdentity();
        void loadMatrix(const mat4 m);
        void loadMatrix(CybFrame& f);
        void multMatrix(const mat4 m);
        void multMatrix(CybFrame& f);
        void pushMatrix();
        void pushMatrix(const mat4 m);
        void pushMatrix(CybFrame& f);
        void popMatrix();
        void rotate(float angle, float x, float y, float z);
        void rotatev(float angle, vec3 axis);
        void scale(float x, float y, float z);
        void scalev(vec3 s);
        void translate(float x, float y, float z);
        void translatev(vec3 t);
    private:
        mat4* stack;
        int depth;
        int pointer;
};


#endif // CYBMATRIXSTACK_H_INCLUDED
