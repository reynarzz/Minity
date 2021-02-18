#pragma once
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include "Texture.h"
#include <vector>

using glm::mat4;

enum RenderingOrder
{
	Back = 1000,
	Opaque = 2000,
	Transparent = 3000,
	UI = 4000
};

class Culling 
{
public:
	bool _enabled;
	int face;
};

class Blending 
{
public:
	bool enabled;
	int _srcFactor;
	int _dstFactor;

};

struct MatAttribs
{
public:
	std::string name;

	// 3 element array
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 transmittance;
	vec3 emission;

	float shininess;
	float ior;       // index of refraction
	float dissolve;  // 1 == opaque; 0 == fully transparent
	int illum;
};

enum RenderMode 
{
   Triangles = GL_TRIANGLES,
   Lines = GL_LINES,
   Points = GL_POINTS
};

class Material
{
public:
	Blending _blending;

	RenderingOrder _renderingOrder = RenderingOrder::Opaque;

	Material(Shader* shader, MatAttribs attribs);
	Material(Shader* shader, MatAttribs attribs, Texture* texture);
	Material(Shader* shader, MatAttribs attribs, std::vector<Texture*> texture);
	~Material();
	void UseMaterial(mat4 viewProjM, vec3 cameraPos);
	Shader* GetShader() const;
	void SetShader(Shader* shader);
	bool _depthWrite = true;
	MatAttribs GetMatAttribs() const;
	Culling culling;
	RenderMode _renderMode;

	void SetModelMatrix(mat4 modelM);

private:
	Shader* _shader;
	mat4 _modelM;
	std::vector<Texture*> _textures;
	MatAttribs attribs;
	//-----------------------TODO-------
	//Texture
	//Color

};

