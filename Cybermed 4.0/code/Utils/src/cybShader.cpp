#include "cybShader.h"

CybShader::CybShader(ifstream& shaderFile, ShaderType t, GLuint& p)
	  : handle(0), type(t), prog(p)
{
    src = readSourceFile(shaderFile);
	cout << "Codigo do shader: " << endl;
	cout << src << endl;
}

CybShader::CybShader(string& s, ShaderType t, GLuint& p)
	  : handle(0), src(s), type(t), prog(p)
{
}

bool CybShader::bindInVariable(GLuint location, const char* name)
{
    if(this->type == VERTEX)
    {
        glBindAttribLocation(handle, location, name);
    }else if(this->type == FRAGMENT)
    {
        glBindFragDataLocation(handle, location, name);
    }else;
}

bool CybShader::compile()
{
    switch(this->type)
    {
        case VERTEX:
            this->handle = glCreateShader(GL_VERTEX_SHADER);
	    cout << "Vertex Shader criado com sucesso, handle: " << handle << endl;
            break;
        case FRAGMENT:
            this->handle = glCreateShader(GL_FRAGMENT_SHADER);
	    cout << "Fragment Shader criado com sucesso, handle: " << handle << endl;
            break;
        case GEOMETRY:
            this->handle = glCreateShader(GL_GEOMETRY_SHADER);
	    cout << "Geometry Shader criado com sucesso, handle: " << handle << endl;
            break;
        case TESS_CONTROL:
            this->handle = glCreateShader(GL_TESS_CONTROL_SHADER);
	    cout << "Tesselation Control Shader criado com sucesso, handle: " << handle << endl;
            break;
        case TESS_EVAL:
            this->handle = glCreateShader(GL_TESS_EVALUATION_SHADER);
	    cout << "Tesselation Evaluation Shader criado com sucesso, handle: " << handle << endl;
            break;
        default:
	    cout << "Nao existe Shader com o tipo passado" << endl;
            return false;
    }    
    const char* cCode = this->src.c_str();
    GLint tam = this->src.size();
    glShaderSource(this->handle, 1, &cCode, &tam);
    glCompileShader(this->handle);
    int result;
    glGetShaderiv(this->handle, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length = 0;
        log = "";
        glGetShaderiv(this->handle, GL_INFO_LOG_LENGTH, &length);
        if(length > 0)
        {
            char* cLog = new char[length];
            int written = 0;
            glGetShaderInfoLog(this->handle, length, &written, cLog);
            log = cLog;
            delete [] cLog;
        }
        return false;
    }else
    {
	cout << "Shader compilado com sucesso. Fazendo o attach." << endl;
        glAttachShader(this->prog, this->handle);
	return true;
    }
}

int CybShader::getHandle()
{
    return this->handle;
}

string CybShader::getLog()
{
    return this->log;
}

string& CybShader::getSourceCode()
{
    return src;
}

string CybShader::readSourceFile(ifstream& shaderFile)
{
    if(!shaderFile) return "";
    ostringstream code;
    while(shaderFile.good())
    {
        int c = shaderFile.get();
        if(!shaderFile.eof()) code << (char) c;
    }
    shaderFile.close();
    return code.str();
}

void CybShader::printDescription()
{
	cout << "Descricao de Shader." << endl;
	cout << "GL Program associado: " << prog << endl;
	cout << "Handle: " << handle << endl;
	cout << "Tipo: " << type << endl;
	cout << "Codigo fonte: \n" << src << endl;
}
