#ifndef CYBSHADERMANAGER_H_INCLUDED
#define CYBSHADERMANAGER_H_INCLUDED

#include "cybShader.h"
#include <cstdlib>

class CybShaderManager
{
    public:
	CybShaderManager(ifstream& vShaderFile, ifstream& fShaderFile);
	CybShaderManager(string vShaderSrcCode, string fShaderSrcCode);
	bool compile();
	int getHandle();
	CybShader* getVertexShader();
	string getLog();
	CybShader* getFragmentShader();
	bool isLinked();
	bool link();
	void printActiveAttributes();
        void printActiveUniforms();
	void setUniform(const char* name, float x, float y, float z);
        void setUniformVec2(const char* name, const vec2 v);
        void setUniformVec3(const char* name, const vec3 v);
        void setUniformVec4(const char* name, const vec4 v);
        void setUniformMat3(const char* name, const mat3 v);
        void setUniformMat4(const char* name, const mat4 v);
        void setUniform(const char* name, const float val);
        void setUniform(const char* name, const int val);
        void setUniform(const char* name, const bool val); 
        void use();
        bool validate();
    private:
    	GLuint handle;
    	bool linked;
    	CybShader* vShader;
    	CybShader* fShader;
    	string log;

	GLint getUniformLocation(const char* name);
};

#endif // CYBSHADERMANAGER_H_INCLUDED
