#include "pch.h"
#include "Shader.h"

#include "Material.h"

Material::Material(Shader* shader) : 
	_shader(shader), _modelM(1.0f)
{
}

Shader* Material::GetShader() const 
{
	return _shader;
}

void Material::UseMaterial(Camera* camera) 
{
	unsigned int id = _shader->UseShader();

	glUseProgram(id);

	_shader->SetUniforms(_modelM, camera);
}

Material::~Material() 
{
	delete _shader;
}