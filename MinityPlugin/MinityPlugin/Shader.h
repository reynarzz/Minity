#pragma once

#include <string>
#include <GL/glew.h>
#include "DebugCPP.h"
#include "Camera.h"

using std::string;

class MatAttribs;

class Shader
{
private:
	unsigned int _programID;
	string _vertexSource;
	string _fragmentSource;
	void Debug(const unsigned int& shaderID, const string& shaderType);
public:

	Shader(const string vertexSource, const string fragmentSource);
	~Shader();
	/// <summary>Sets up the shader program and returns it</summary>
	/// <returns>Shader program ID</returns>
	void SetUniforms(mat4 model, MatAttribs attribs, Camera* camera);
	unsigned int UseShader();
	unsigned int GetProgramID() const;
	void Clear();
};