#include "pch.h"
#include "Shader.h"

#include "Material.h"

Material::Material(Shader* shader, MatAttribs attribs) :
	Material::Material(shader, attribs, new Texture("MinityRes/Textures/defaultText.png"))
{
}

Material::Material(Shader* shader, MatAttribs attribs, Texture* texture) :
	_shader(shader), attribs(attribs), _modelM(1.0f), _renderingOrder(RenderingOrder::Opaque)
{
	if (texture == nullptr)
	{
		//texture = new Texture("OBJModels/Medieval/emptyTex.png");
	}

	_textures.push_back(texture);
}

Material::Material(Shader* shader, MatAttribs attribs, std::vector<Texture*> textures) :
	_shader(shader), attribs(attribs), _modelM(1.0f), _textures(textures), _renderingOrder(RenderingOrder::Opaque)
{
}

Shader* Material::GetShader() const
{
	return _shader;
}

MatAttribs Material::GetMatAttribs() const 
{
	return attribs;
}

void Material::SetModelMatrix(mat4 model) 
{
	_modelM = model;
}

void Material::UseMaterial(Camera* camera)
{
	unsigned int id = _shader->UseShader();

	glUseProgram(id);

	for (unsigned int i = 0; i < _textures.size(); i++)
	{
		_textures[i]->Bind(i);
	}

	_shader->SetUniforms(_modelM, attribs, camera);
}

Material::~Material()
{
	delete _shader;
}