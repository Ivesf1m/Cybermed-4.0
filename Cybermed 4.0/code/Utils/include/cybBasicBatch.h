#ifndef _CYBBASICBATCH_H_
#define _CYBBASICBATCH_H_

#include <GL/glew.h>
#include <cstring>
#include "cybVector.h"
#include "cybBatch.h"

class CybBasicBatch : public CybBatch
{
	public:
		CybBasicBatch();
		virtual ~CybBasicBatch();
		void begin(GLenum primitive, GLuint nVerts, GLuint nTexUnits = 0);
		void color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		void color4fv(vec4 color);
		void colorData4f(vec4* colors);
		virtual void draw();
		void end();
		void normal3f(GLfloat x, GLfloat y, GLfloat z);
		void normal3fv(vec3 normal);
		void normalData3f(vec3* normals);
		void reset();
		void texCoord2f(GLuint texture, GLclampf s, GLclampf t);
		void texCoord2fv(GLuint texture, vec2 texCoords);
		void texCoordData2f(vec2* texCoords, GLuint texLayer);
		void vertex3f(GLfloat x, GLfloat y, GLfloat z);
		void vertex3fv(vec3 vertex);
		void vertexData3f(vec3* verts);
	private:
		GLenum primitive;
		GLuint vArrayHandle;
		GLuint nArrayHandle;
		GLuint cArrayHandle;
		GLuint* tcArrayHandles;
		GLuint vao; //vertex array object
		GLuint currNumVerts; //current number of vertices
		GLuint numVerts; //total number of vertices
		GLuint numTexUnits;
		bool done;
		vec3* vArray;
		vec3* nArray;
		vec4* cArray;
		vec2** tcArrays;

		void generateBuffer2D(GLuint* handle, vec2* array);
		void generateBuffer3D(GLuint* handle, vec3* array);
		void generateBuffer4D(GLuint* handle, vec4* array);
};

#endif //_CYBBASICBATCH_H_