#include "pch.h"
#include "ShaderUtils.h"

ShadersSource ParseShader(const string shaderFilePath)
{
	std::ifstream stream(shaderFilePath);

	enum class ShaderType
	{
		NONE = 2, VERTEX = 0, FRAGMENT = 1
	};

	string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	int sT = 0;

	while (std::getline(stream, line))
	{
		std::cout << line << std::endl;

		if (line.find("#shader") != string::npos)
		{
			if (line.find("VERTEX") != string::npos)
			{
				type = ShaderType::VERTEX;
				sT = 0;
			}
			else if (line.find("FRAGMENT") != string::npos)
			{
				type = ShaderType::FRAGMENT;
				sT = 1;
			}
		}
		else
		{
			ss[sT] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

