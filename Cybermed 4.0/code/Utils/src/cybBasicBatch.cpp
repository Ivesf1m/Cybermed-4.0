#include "cybBasicBatch.h"

CybBasicBatch::CybBasicBatch()
{
	numTexUnits = 0;
	numVerts = 0;
	vArray = NULL;
	nArray = NULL;
	cArray = NULL;
	tcArrays = NULL;
	vArrayHandle = 0;
	nArrayHandle = 0;
	cArrayHandle = 0;
	vao = 0;
	done = false;
	currNumVerts = 0;
	tcArrays - NULL;
}

CybBasicBatch::~CybBasicBatch()
{
	if(vArrayHandle) glDeleteBuffers(1, &vArrayHandle);
	if(nArrayHandle) glDeleteBuffers(1, &nArrayHandle);
	if(cArrayHandle) glDeleteBuffers(1, &cArrayHandle);
	for(unsigned int i = 0; i < numTexUnits; ++i){
		glDeleteBuffers(1, &tcArrayHandles[i]);
	}
	glDeleteVertexArrays(1, &vao);

	delete [] tcArrayHandles;
	delete [] tcArrays;
}

void CybBasicBatch::begin(GLenum primitive, GLuint nVerts, GLuint nTexUnits)
{
	this->primitive = primitive;
	numVerts = nVerts;
	numTexUnits = nTexUnits > 4 ? 4 : nTexUnits;
	if(numTexUnits != 0){
		tcArrayHandles = new GLuint[numTexUnits];
		for(unsigned int i = 0; i < numTexUnits; ++i){
			tcArrayHandles[i] = 0;
			tcArrays[i] = NULL;
		}
	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void CybBasicBatch::color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	if(cArrayHandle == 0) generateBuffer4D(&cArrayHandle, NULL);
	if(!cArray){
		glBindBuffer(GL_ARRAY_BUFFER, cArrayHandle);
		cArray = (vec4*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;

	cArray[currNumVerts][0] = r;
	cArray[currNumVerts][1] = g;
	cArray[currNumVerts][2] = b;
	cArray[currNumVerts][3] = a;
}

void CybBasicBatch::color4fv(vec4 color)
{
	if(cArrayHandle == 0) generateBuffer4D(&cArrayHandle, NULL);
	if(!cArray){
		glBindBuffer(GL_ARRAY_BUFFER, cArrayHandle);
		cArray = (vec4*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;
	memcpy(cArray[currNumVerts], color, sizeof(vec4));
}

void CybBasicBatch::colorData4f(vec4* colors)
{
	if(cArrayHandle == 0) generateBuffer4D(&cArrayHandle, colors);
	else glBindBuffer(GL_ARRAY_BUFFER, cArrayHandle);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * numVerts, colors);
	cArray = NULL;
}

void CybBasicBatch::draw()
{
	if(!done) return;
	glBindVertexArray(vao);
	glDrawArrays(primitive, 0, numVerts);
	glBindVertexArray(0);
}

void CybBasicBatch::end()
{
	if(vArray){
		glBindBuffer(GL_ARRAY_BUFFER, vArrayHandle);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		vArray = NULL;
	}
	if(nArray){
		glBindBuffer(GL_ARRAY_BUFFER, nArrayHandle);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		nArray = NULL;
	}
	if(cArray){
		glBindBuffer(GL_ARRAY_BUFFER, cArrayHandle);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		cArray = NULL;
	}
	for(unsigned int i = 0; i < numTexUnits; ++i){
		if(	tcArrays[i]){
			glBindBuffer(GL_ARRAY_BUFFER, tcArrayHandles[i]);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			tcArrays[i] = NULL;
		}
	}
	glBindVertexArray(vao);

	if(vArrayHandle){
		glEnableVertexAttribArray(VERTEX_ATTRIB);
		glBindBuffer(GL_ARRAY_BUFFER, vArrayHandle);
		glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	if(nArrayHandle){
		glEnableVertexAttribArray(NORMAL_ATTRIB);
		glBindBuffer(GL_ARRAY_BUFFER, nArrayHandle);
		glVertexAttribPointer(NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	if(cArrayHandle){
		glEnableVertexAttribArray(COLOR_ATTRIB);
		glBindBuffer(GL_ARRAY_BUFFER, cArrayHandle);
		glVertexAttribPointer(COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}
	for(unsigned int i = 0; i < numTexUnits; ++i){
		if(tcArrayHandles[i]){
			glEnableVertexAttribArray(TEXTURE0_ATTRIB + i);
			glBindBuffer(GL_ARRAY_BUFFER, tcArrayHandles[i]);
			glVertexAttribPointer(TEXTURE0_ATTRIB + i, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}
	}
	done = true;
	glBindVertexArray(vao);
}

void CybBasicBatch::generateBuffer2D(GLuint* handle, vec2* array)
{
	glGenBuffers(1, handle);
	glBindBuffer(GL_ARRAY_BUFFER, *handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * numVerts, array, GL_DYNAMIC_DRAW);
}

void CybBasicBatch::generateBuffer3D(GLuint* handle, vec3* array)
{
	glGenBuffers(1, handle);
	glBindBuffer(GL_ARRAY_BUFFER, *handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * numVerts, array, GL_DYNAMIC_DRAW);
}

void CybBasicBatch::generateBuffer4D(GLuint* handle, vec4* array)
{
	glGenBuffers(1, handle);
	glBindBuffer(GL_ARRAY_BUFFER, *handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * numVerts, array, GL_DYNAMIC_DRAW);
}

void CybBasicBatch::normal3f(GLfloat x, GLfloat y, GLfloat z)
{
	if(nArrayHandle == 0) generateBuffer3D(&nArrayHandle, NULL);
	if(!nArray){
		glBindBuffer(GL_ARRAY_BUFFER, nArrayHandle);
		nArray = (vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;

	nArray[currNumVerts][0] = x;
	nArray[currNumVerts][1] = y;
	nArray[currNumVerts][2] = z;
}

void CybBasicBatch::normal3fv(vec3 normal)
{
	if(nArrayHandle == 0) generateBuffer3D(&nArrayHandle, NULL);
	if(!nArray){
		glBindBuffer(GL_ARRAY_BUFFER, nArrayHandle);
		nArray = (vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;

	memcpy(nArray[currNumVerts], normal, sizeof(vec3));
}

void CybBasicBatch::normalData3f(vec3* normals)
{
	if(nArrayHandle == 0) generateBuffer3D(&nArrayHandle, normals);
	else glBindBuffer(GL_ARRAY_BUFFER, nArrayHandle);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * numVerts, normals);
	nArray = NULL;
}

void CybBasicBatch::reset()
{
	done = false;
	currNumVerts = 0;
}

void CybBasicBatch::texCoord2f(GLuint texture, GLclampf s, GLclampf t)
{
	if(tcArrayHandles[texture] == 0) generateBuffer2D(&tcArrayHandles[texture], NULL);
	if(!tcArrays[texture]){
		glBindBuffer(GL_ARRAY_BUFFER, tcArrayHandles[texture]);
		tcArrays[texture] = (vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;

	tcArrays[texture][currNumVerts][0] = s;
	tcArrays[texture][currNumVerts][1] = t;
}

void CybBasicBatch::texCoord2fv(GLuint texture, vec2 texCoords)
{
	if(tcArrayHandles[texture] == 0) generateBuffer2D(&tcArrayHandles[texture], NULL);
	if(!tcArrays[texture]){
		glBindBuffer(GL_ARRAY_BUFFER, tcArrayHandles[texture]);
		tcArrays[texture] = (vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;
	memcpy(tcArrays[texture], texCoords, sizeof(vec2));
}

void CybBasicBatch::texCoordData2f(vec2* texCoords, GLuint texLayer)
{
	if(tcArrayHandles[texLayer] == 0) generateBuffer2D(&tcArrayHandles[texLayer], texCoords);
	else glBindBuffer(GL_ARRAY_BUFFER, tcArrayHandles[texLayer]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GL_FLOAT) * 2 * numVerts, texCoords);
	tcArrays[texLayer] = NULL;
}

void CybBasicBatch::vertex3f(GLfloat x, GLfloat y, GLfloat z)
{
	if(vArrayHandle == 0) generateBuffer3D(&vArrayHandle, NULL);
	if(!vArray){
		glBindBuffer(GL_ARRAY_BUFFER, vArrayHandle);
		vArray = (vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;

	vArray[currNumVerts][0] = x;
	vArray[currNumVerts][1] = y;
	vArray[currNumVerts][2] = z;
	++currNumVerts;
}

void CybBasicBatch::vertex3fv(vec3 vertex)
{
	if(vArrayHandle == 0) generateBuffer3D(&vArrayHandle, NULL);
	if(!vArray){
		glBindBuffer(GL_ARRAY_BUFFER, vArrayHandle);
		vArray = (vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if(currNumVerts >= numVerts) return;
	memcpy(vArray[currNumVerts], vertex, sizeof(vec3));
	++currNumVerts;
}

void CybBasicBatch::vertexData3f(vec3* verts)
{
	if(vArrayHandle == 0) generateBuffer3D(&vArrayHandle, verts);
	else glBindBuffer(GL_ARRAY_BUFFER, vArrayHandle);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * numVerts, verts);
	vArray = NULL;
}