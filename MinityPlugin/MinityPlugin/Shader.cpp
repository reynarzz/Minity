#include "pch.h"

#include "Shader.h"


Shader::Shader(string vertexSource, string fragmentSource) 
	:_vertexSource(vertexSource), _fragmentSource(fragmentSource), _programID(-1)
{
}

unsigned int Shader::BuildShader()
{
	_programID = glCreateProgram();

	unsigned int vsID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fsID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vSource = _vertexSource.c_str();
	const char* fSource = _fragmentSource.c_str();

	glShaderSource(vsID, 1, &vSource, 0);
	glShaderSource(fsID, 1, &fSource, 0);

	glCompileShader(vsID);
	glCompileShader(fsID);

	glAttachShader(_programID, vsID);
	glAttachShader(_programID, fsID);

	glLinkProgram(_programID);
	glValidateProgram(_programID);

	glDeleteShader(vsID);
	glDeleteShader(fsID);

	Debug::Log(_vertexSource);
	Debug::Log(_fragmentSource);

	return _programID;
}

unsigned int Shader::GetProgramID() const 
{
	if (_programID == -1)
	{
		Debug::Log("ERROR: Getting Shader program before building it!!");
	}
	
	return _programID;
}

Shader::~Shader() { }