#ifndef CYBSHADER_H_INCLUDED
#define CYBSHADER_H_INCLUDED

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "cybVector.h"
#include "cybLineMatrix.h"

using namespace std;

enum ShaderType
{
    VERTEX, FRAGMENT, GEOMETRY,
    TESS_CONTROL, TESS_EVAL
};

enum ShaderAttribute
{
    VERTEX_ATTRIB, NORMAL_ATTRIB, COLOR_ATTRIB,
    TEXTURE0_ATTRIB, TEXTURE1_ATTRIB,
    TEXTURE2_ATTRIB, TEXTURE3_ATTRIB
};

class CybShader
{
    public:
            CybShader(ifstream&, ShaderType, GLuint&);
            CybShader(string&, ShaderType, GLuint&);
            bool bindInVariable(GLuint location, const char* name);
            bool compile();
            int getHandle();
            string getLog();
	    string& getSourceCode();
	    void printDescription();             
                       
    private:
            GLuint handle;
            GLuint prog;            
            string log;
            string src;
            ShaderType type;

            string readSourceFile(ifstream& shaderFile);
};

#endif // CYBSHADER_H_INCLUDED
