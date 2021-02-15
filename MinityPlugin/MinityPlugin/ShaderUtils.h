#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::string;

struct ShadersSource
{
	string vertexSource;
	string fragmentSource;
};

ShadersSource ParseShader(const string shaderFilePath);