#pragma once
#include "Shader.h"
#include <glm/glm.hpp>

class Material
{
private:
	Shader* _shader;
	mat4 _modelM;
	//Texture
	//Color
public:
	Material(Shader* shader);
	~Material();
	void UseMaterial(Camera* camera);
	Shader* GetShader() const;
};

