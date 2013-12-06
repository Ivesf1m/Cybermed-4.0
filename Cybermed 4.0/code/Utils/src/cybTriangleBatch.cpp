#include "cybTriangleBatch.h"

#define epsilon 1e-5

CybTriangleBatch::CybTriangleBatch()
{
	indexArray = NULL;
	vArray = NULL;
	nArray = NULL;
	tcArray = NULL;

	numInds = 0;
	currNumVerts = 0;
	currNumInds = 0;
}

CybTriangleBatch::~CybTriangleBatch()
{
	delete [] indexArray;
	delete [] vArray;
	delete [] nArray;
	delete [] tcArray;

	glDeleteBuffers(4, vbo);
	glDeleteVertexArrays(1, &vao);
}

void CybTriangleBatch::addTriangle(vec3 verts[3], vec3 norms[3], vec2 texCoords[3])
{
	for(int i = 0; i < 3; ++i){
		float length = norms[i][0] * norms[i][0] + norms[i][1] * norms[i][1] + norms[i][2] * norms[i][2];
		length = sqrt(length);
		norms[i][0] /= length; norms[i][1] /= length; norms[i][2] /= length;
	}
	for(GLuint i = 0; i < 3; ++i){
		GLuint match = 0;
		for(match = 0; match < currNumVerts; match++){
			if(isNumericallyEqual(vArray[match][0], verts[i][0], epsilon) &&
			   isNumericallyEqual(vArray[match][1], verts[i][1], epsilon) &&
			   isNumericallyEqual(vArray[match][2], verts[i][2], epsilon) &&

			   isNumericallyEqual(nArray[match][0], norms[i][0], epsilon) &&
			   isNumericallyEqual(nArray[match][1], norms[i][1], epsilon) &&
			   isNumericallyEqual(nArray[match][2], norms[i][2], epsilon) &&

			   isNumericallyEqual(tcArray[match][0], texCoords[i][0], epsilon) &&
			   isNumericallyEqual(tcArray[match][1], texCoords[i][1], epsilon)){
					indexArray[currNumInds] = match;
					++currNumInds;
					break;
			}
		}
		if(match == currNumVerts && currNumVerts < numInds && currNumInds < numInds){
			memcpy(vArray[currNumVerts], verts[i], sizeof(vec3));
			memcpy(nArray[currNumVerts], norms[i], sizeof(vec3));
			memcpy(tcArray[currNumVerts], texCoords[i], sizeof(vec2));
			indexArray[currNumInds] = currNumVerts;
			++currNumInds;
			++currNumVerts;
		}
	}
}

void CybTriangleBatch::begin(GLuint maxNumVerts)
{
	delete [] indexArray;
	delete [] vArray;
	delete [] nArray;
	delete [] tcArray;

	numInds = maxNumVerts;
	currNumVerts = 0;
	currNumInds = 0;

	indexArray = new GLushort[numInds];
	vArray = new vec3[numInds];
	nArray = new vec3[numInds];
	tcArray = new vec2[numInds];
}

void CybTriangleBatch::draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, currNumInds, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
}

void CybTriangleBatch::end()
{
	cout << "Numero de indices: " << numInds << endl;
	cout << "Vertices: " << endl;
	for(int i = 0; i < numInds; ++i){
		cout << vArray[i][0] << "    " << vArray[i][1] << "    " << vArray[i][2] << endl;
	}
	cout << "Normais: " << endl;
	for(int i = 0; i < numInds; ++i){
		cout << nArray[i][0] << "    " << nArray[i][1] << "    " << nArray[i][2] << endl;
	}
	cout << "Indices: " << endl;
	for(int i = 0; i < numInds; ++i){
		cout << i << ":    " << indexArray[i] << "    " << indexArray[i] << "    " << indexArray[i] << endl;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(4, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_DATA]);
	glEnableVertexAttribArray(VERTEX_ATTRIB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * currNumVerts * 3, vArray, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(vArray[0]), 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_DATA]);
	glEnableVertexAttribArray(NORMAL_ATTRIB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * currNumVerts * 3, nArray, GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(nArray[0]), 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXTURE_DATA]);
	glEnableVertexAttribArray(TEXTURE0_ATTRIB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * currNumVerts * 2, tcArray, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTURE0_ATTRIB, 2, GL_FLOAT, GL_FALSE, sizeof(tcArray[0]), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_DATA]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * currNumInds, indexArray, GL_STATIC_DRAW);

	glBindVertexArray(0);

	delete [] indexArray;
	delete [] vArray;
	delete [] nArray;
	delete [] tcArray;

	indexArray = NULL;
	vArray = NULL;
	nArray = NULL;
	tcArray = NULL;

	glBindVertexArray(0);
}

GLuint CybTriangleBatch::getCurrentIndexCount()
{
	return currNumInds;
}

GLuint CybTriangleBatch::getCurrentVertexCount()
{
	return currNumVerts;
}

bool CybTriangleBatch::isNumericallyEqual(float f1, float f2, float error)
{
	return (fabs(f1 - f2) < error);
}
