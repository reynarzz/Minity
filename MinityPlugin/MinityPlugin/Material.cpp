#include "pch.h"
#include "Shader.h"

#include "Material.h"

Material::Material(Shader* shader) : Material::Material(shader, new Texture("OBJModels/Medieval/emptyTex.png"))
{
}

Material::Material(Shader* shader, Texture* texture) :
	_shader(shader), _modelM(1.0f)
{
	if (texture == nullptr)
	{
		//texture = new Texture("OBJModels/Medieval/emptyTex.png");
	}

	_textures.push_back(texture);
}

Shader* Material::GetShader() const
{
	return _shader;
}

void Material::BindTextures()
{
}

void Material::UseMaterial(Camera* camera)
{
	unsigned int id = _shader->UseShader();

	glUseProgram(id);

	//auto value = _textures.size();

	for (unsigned int i = 0; i < _textures.size(); i++)
	{
		_textures[i]->Bind(i);
	}

	_shader->SetUniforms(_modelM, camera);
}

Material::~Material()
{
	delete _shader;
}