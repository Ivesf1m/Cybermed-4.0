#include "cybMatrixStack.h"

#define PI 3.141592
#define DEGTORAD(x) (x * PI / 180.0)

CybMatrixStack::CybMatrixStack(int depth)
{
    this->depth = depth;
    this->stack = new mat4[depth];
    this->pointer = 0;
    CybLineMatrix::loadIdentity4D(this->stack[0]);
}

CybMatrixStack::~CybMatrixStack()
{
    delete [] this->stack;
}

mat4& CybMatrixStack::getMatrix()
{
    return this->stack[pointer];
}

void CybMatrixStack::getMatrix(mat4 m)
{
    CybLineMatrix::copyMatrix4D(stack[pointer], m);
}

void CybMatrixStack::loadIdentity()
{
    CybLineMatrix::loadIdentity4D(stack[pointer]);
}

void CybMatrixStack::loadMatrix(const mat4 m)
{
    CybLineMatrix::copyMatrix4D(m, stack[pointer]);
}

void CybMatrixStack::loadMatrix(CybFrame& f)
{
    mat4 m;
    f.getFrameMatrix(m);
    this->loadMatrix(m);
}

void CybMatrixStack::multMatrix(const mat4 m)
{
    mat4 aux;
    CybLineMatrix::copyMatrix4D(stack[pointer], aux);
    CybLineMatrix::multiplyMatrices4D(aux, m, stack[pointer]);
}

void CybMatrixStack::multMatrix(CybFrame& f)
{
    mat4 m;
    f.getFrameMatrix(m);
    this->multMatrix(m);
}

void CybMatrixStack::pushMatrix()
{
    if(pointer < depth)
    {
        pointer++;
        CybLineMatrix::copyMatrix4D(stack[pointer-1], stack[pointer]);
    }else cout << "Full stack. Pop some matrices." << endl;
}

void CybMatrixStack::pushMatrix(const mat4 m)
{
    if(pointer < depth)
    {
        pointer++;
        CybLineMatrix::copyMatrix4D(m, stack[pointer]);
    }else cout << "Full stack. Pop some matrices." << endl;
}

void CybMatrixStack::pushMatrix(CybFrame& f)
{
    mat4 m;
    f.getFrameMatrix(m);
    this->pushMatrix(m);
}

void CybMatrixStack::popMatrix()
{
    if(pointer > 0) --pointer;
    else cout << "Empty stack." << endl;
}

void CybMatrixStack::rotate(float angle, float x, float y, float z)
{
    mat4 aux, rot;
    CybLineMatrix::createRotationMatrix4D(rot, DEGTORAD(angle), x, y, z);
    CybLineMatrix::copyMatrix4D(stack[pointer], aux);
    CybLineMatrix::multiplyMatrices4D(aux, rot, stack[pointer]);
}

void CybMatrixStack::rotatev(float angle, vec3 axis)
{
    mat4 aux, rot;
    CybLineMatrix::createRotationMatrix4D(rot, DEGTORAD(angle), axis[0], axis[1], axis[2]);
    CybLineMatrix::copyMatrix4D(stack[pointer], aux);
    CybLineMatrix::multiplyMatrices4D(aux, rot, stack[pointer]);
}

void CybMatrixStack::scale(float x, float y, float z)
{
    mat4 aux, scale;
    CybLineMatrix::createScaleMatrix4D(scale, x, y, z);
    CybLineMatrix::copyMatrix4D(stack[pointer], aux);
    CybLineMatrix::multiplyMatrices4D(aux, scale, stack[pointer]);
}

void CybMatrixStack::scalev(vec3 s)
{
    mat4 aux, scale;
    CybLineMatrix::createScaleMatrix4D(scale, s[0], s[1], s[2]);
    CybLineMatrix::copyMatrix4D(stack[pointer], aux);
    CybLineMatrix::multiplyMatrices4D(aux, scale, stack[pointer]);
}

void CybMatrixStack::translate(float x, float y, float z)
{
    mat4 aux, trans;
    CybLineMatrix::createTranslationMatrix4D(trans, x, y, z);
    CybLineMatrix::copyMatrix4D(stack[pointer], aux);
    CybLineMatrix::multiplyMatrices4D(aux, trans, stack[pointer]);
}

void CybMatrixStack::translatev(vec3 t)
{
    mat4 aux, trans;
    CybLineMatrix::loadIdentity4D(trans);
    CybLineMatrix::setColumn4D(trans, t, 3);
    CybLineMatrix::copyMatrix4D(stack[pointer], aux);
    CybLineMatrix::multiplyMatrices4D(aux, trans, stack[pointer]);
}
