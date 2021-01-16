#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>

class Material
{
private:
	Shader* _shader;
	mat4 _modelM;
	std::vector<Texture*> _textures;

	//Texture
	//Color
public:
	Material(Shader* shader);
	Material(Shader* shader, Texture* texture);
	Material(Shader* shader, std::vector<Texture*> texture);
	~Material();
	void UseMaterial(Camera* camera);
	Shader* GetShader() const;
	void BindTextures();
};

