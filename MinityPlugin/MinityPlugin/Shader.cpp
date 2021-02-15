#include "pch.h"

#include "Shader.h"
#include <iostream>

Shader::Shader(const string vertexSource, const string fragmentSource) 
	:_vertexSource(vertexSource), _fragmentSource(fragmentSource), _programID(0)
{
}

void Shader::Debug(const unsigned int& shaderID, const string& shaderType) 
{
	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) 
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* error = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, error);

		Debug::Log(shaderType);
		Debug::Log(error);
	}
}

unsigned int Shader::UseShader()
{
	if (_programID == 0) 
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

		/*Debug(vsID, "Vertex shader");
		Debug(vsID, "Fragment shader");
		Debug::Log("Create shader");*/
		glAttachShader(_programID, vsID);
		glAttachShader(_programID, fsID);

		glLinkProgram(_programID);
		glValidateProgram(_programID);

		glDeleteShader(vsID);
		glDeleteShader(fsID);

		//Debug::Log(_vertexSource);
		//Debug::Log(_fragmentSource);
	}
	
	return _programID;
}
void Shader::SetUniforms(mat4 model, glm::vec4 ambient,  Camera* camera)
{
	unsigned int uniformModelID = glGetUniformLocation(_programID, "_MVP");
	unsigned int matAmbientID = glGetUniformLocation(_programID, "_AMBIENT");

	mat4 viewProjM = camera->GetViewProjMatrix();

	//modelTest = glm::rotate(modelTest, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniform4f(matAmbientID, ambient.r, ambient.g, ambient.b, ambient.a);
	glUniformMatrix4fv(uniformModelID, 1, GL_FALSE, glm::value_ptr(viewProjM * model));
}

unsigned int Shader::GetProgramID() const 
{
	if (_programID == -1)
	{
		Debug::Log("ERROR: Getting Shader program before building it!!");
	}
	
	return _programID;
}

void Shader::Clear() 
{
	glDeleteProgram(_programID);
	_programID = 0;
}

Shader::~Shader() { }