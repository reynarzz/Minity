#pragma once
#include "Shader.h"

class Material
{
private:
	Shader* _shader;
	//Texture
	//Color
public:
	Material(Shader* shader);
	~Material();
	Shader* GetShader() const;
};

