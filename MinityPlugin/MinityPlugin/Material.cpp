#include "pch.h"
#include "Shader.h"

#include "Material.h"

Material::Material(Shader* shader) : 
	_shader(shader)
{
}

Shader* Material::GetShader() const 
{
	return _shader;
}

Material::~Material() 
{
	delete _shader;
}