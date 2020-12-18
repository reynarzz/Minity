#pragma once

#include <string>
#include <GL/glew.h>
#include "DebugCPP.h"


using std::string;

class Shader
{
private:
	unsigned int _programID;
	string& _vertexSource;
	string& _fragmentSource;
public:

	Shader(string& vertexSource, string& fragmentSource);
	~Shader();
	/// <summary>Sets up the shader program and returns it</summary>
	/// <returns>Shader program.</returns>
	unsigned int BuildShader();
	unsigned int GetProgramID() const;
};