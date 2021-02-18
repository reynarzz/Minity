#include "pch.h"
#include "Shader.h"

#include "Material.h"

Material::Material(Shader* shader, MatAttribs attribs) :
	Material::Material(shader, attribs, new Texture("MinityRes/Textures/defaultText.png"))
{
}

Material::Material(Shader* shader, MatAttribs attribs, Texture* texture) :
	_shader(shader), attribs(attribs), _modelM(1.0f), 
	_renderingOrder(RenderingOrder::Opaque), _renderMode(RenderMode::Triangles)
{
	if (texture == nullptr)
	{
		//texture = new Texture("OBJModels/Medieval/emptyTex.png");
	}

	_textures.push_back(texture);
}

Material::Material(Shader* shader, MatAttribs attribs, std::vector<Texture*> textures) :
	_shader(shader), attribs(attribs), _modelM(1.0f), _textures(textures), 
	_renderingOrder(RenderingOrder::Opaque), _renderMode(RenderMode::Triangles)
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

void Material::SetShader(Shader* shader) 
{
	_shader = shader;
}

void Material::UseMaterial(mat4 viewProjM, vec3 cameraPos)
{
	unsigned int id = _shader->UseShader();

	glUseProgram(id);

	for (unsigned int i = 0; i < _textures.size(); i++)
	{
		_textures[i]->Bind(i);
	}

	_shader->SetUniforms(viewProjM * _modelM, cameraPos, attribs);
}

Material::~Material()
{
	delete _shader;
}