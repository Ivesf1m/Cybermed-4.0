#include "cybShaderManager.h"

CybShaderManager::CybShaderManager(ifstream& vShaderFile, ifstream& fShaderFile)
{
	linked = false;
	cout << "criando handle" << endl;
	handle = glCreateProgram();
	cout << "handle criado" << endl;
	if(!handle){
		cout << "Nao foi possivel criar o Shader Program" << endl;
		exit(1);
	}
	cout << "Novo Shader Program criado, handle: " << handle << endl;
	vShader = new CybShader(vShaderFile, VERTEX, handle);
	fShader = new CybShader(fShaderFile, FRAGMENT, handle);
}

CybShaderManager::CybShaderManager(string vShaderSrcCode, string fShaderSrcCode)
{
	linked = false;
	handle = glCreateProgram();
	if(!handle){
		cout << "Nao foi possivel criar o Shader Program" << endl;
		exit(1);
	}
	cout << "Novo Shader Program criado, handle: " << handle << endl;
	vShader = new CybShader(vShaderSrcCode, VERTEX, handle);
	fShader = new CybShader(fShaderSrcCode, FRAGMENT, handle);
}

bool CybShaderManager::compile()
{
	bool status = vShader->compile();
	if(!status) this->log = vShader->getLog();
	cout << this->log << endl;
	status = fShader->compile();
	if(!status) this->log = fShader->getLog();
	cout << this->log << endl;
}

CybShader* CybShaderManager::getVertexShader()
{
	return vShader;
}

int CybShaderManager::getHandle()
{
	return handle;
}

CybShader* CybShaderManager::getFragmentShader()
{
	return fShader;
}

string CybShaderManager::getLog()
{
	return log;
}

GLint CybShaderManager::getUniformLocation(const char* name)
{
    return glGetUniformLocation(handle, name);
}

bool CybShaderManager::isLinked()
{
	return linked;
}

bool CybShaderManager::link()
{
	if(linked){
		cout << "entrou no if do link" << endl;
		return true;
	}
	if(handle <= 0) return false;
	glLinkProgram(handle);
	int status = 0;
	glGetProgramiv(handle, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		int length = 0;
		log = "";
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
		if(length > 0){
			char* cLog = new char[length];
			int written = 0;
			glGetProgramInfoLog(handle, length, &written, cLog);
			log = cLog;
			delete [] cLog;
		}
		return false;
	}else{
		linked = true;
		cout << "O programa de handle " << handle << " foi linkado com sucesso." << endl;
		return linked;
	}
}

void CybShaderManager::printActiveAttributes()
{
	GLint written, size, location, maxLength, nAttribs;
	GLchar* name;
	GLenum type;

	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
	name = new GLchar[maxLength];
	printf(" Index | Name\n");
	printf("-----------------------------------------\n");
	for(int i = 0; i < nAttribs; ++i){
		glGetActiveAttrib(handle, i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(handle, name);
		printf(" %-5d | %s\n", location, name);
	}
	delete [] name;
}

void CybShaderManager::printActiveUniforms()
{
	GLint written, size, location, maxLength, nUniforms;
	GLchar* name;
	GLenum type;

	glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &nUniforms);
	name = new GLchar[maxLength];
	printf(" Location | Name\n");
	printf("-----------------------------------------\n");
	for(int i = 0; i < nUniforms; ++i){
		glGetActiveUniform(handle, i, maxLength, &written, &size, &type, name);
		location = glGetUniformLocation(handle, name);
		printf(" %-8d | %s\n", location, name);
	}
	delete [] name;
}

void CybShaderManager::setUniform(const char* name, float x, float y, float z)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniform3f(loc, x, y, z);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::setUniformVec2(const char* name, const vec2 v)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniform2f(loc, v[0], v[1]);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::setUniformVec3(const char* name, const vec3 v)
{
    setUniform(name, v[0], v[1], v[2]);
}

void CybShaderManager::setUniformVec4(const char* name, const vec4 v)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniform4f(loc, v[0], v[1], v[2], v[3]);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::setUniformMat3(const char* name, const mat3 v)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniformMatrix3fv(loc, 1, GL_FALSE, v);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::setUniformMat4(const char* name, const mat4 v)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniformMatrix4fv(loc, 1, GL_FALSE, v);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::setUniform(const char* name, const float val)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniform1f(loc, val);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::setUniform(const char* name, const int val)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniform1i(loc, val);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::setUniform(const char* name, const bool val)
{
    GLint loc = getUniformLocation(name);
    if(loc >= 0) glUniform1i(loc, val);
    else cout << "A variavel uniforme " << name << " nao foi encontrada" << endl;
}

void CybShaderManager::use()
{
	if(handle <= 0 || !linked) return;
	glUseProgram(handle);
}

bool CybShaderManager::validate()
{
	if(!linked)
	{
		cout << "entrei no if do validate" << endl;
		return false;
	}
	GLint status;
	glValidateProgram(handle);
	glGetProgramiv(handle, GL_VALIDATE_STATUS, &status);
	if(status == GL_FALSE){
		int length = 0;
		log = "";
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
		if(length > 0){
			char* cLog = new char[length];
			int written = 0;
			glGetProgramInfoLog(handle, length, &written, cLog);
			log = cLog;
			delete [] cLog;
		}
		return false;
	}else
	{
		cout << "Programa de handle " << handle << " validado com sucesso." << endl;
		return true;
	}
}
