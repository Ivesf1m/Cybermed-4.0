#ifndef _CYBTRIANGLEBATCH_H_
#define _CYBTRIANGLEBATCH_H_

#include "cybBatch.h"
#include "cybVector.h"
#include "cybShader.h"

#define VERTEX_DATA 0
#define NORMAL_DATA 1
#define TEXTURE_DATA 2
#define INDEX_DATA 3


class  CybTriangleBatch : public CybBatch
{
	public:
		CybTriangleBatch();
		virtual ~CybTriangleBatch();
		void addTriangle(vec3 verts[3], vec3 norms[3], vec2 texCoords[3]);
		void begin(GLuint maxNumVerts);
		virtual void draw();
		void end();
		GLuint getCurrentIndexCount();
		GLuint getCurrentVertexCount();
	private:
		GLushort* indexArray;
		vec3* vArray;
		vec3* nArray;
		vec2* tcArray;

		GLuint numInds;
		GLuint currNumVerts;
		GLuint currNumInds;
		GLuint vbo[4];
		GLuint vao;

		bool isNumericallyEqual(float f1, float f2, float error);
};


#endif //_CYBTRIANGLEBATCH_H_
