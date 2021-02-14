#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>
#include <glm/glm.hpp>

class Material
{
public:
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

	Material(Shader* shader, MatAttribs attribs);
	Material(Shader* shader, MatAttribs attribs, Texture* texture);
	Material(Shader* shader, MatAttribs attribs, std::vector<Texture*> texture);
	~Material();
	void UseMaterial(Camera* camera);
	Shader* GetShader() const;
	void BindTextures();

	MatAttribs GetMatAttribs() const;

private:
	Shader* _shader;
	mat4 _modelM;
	std::vector<Texture*> _textures;
	MatAttribs attribs;
	//-----------------------TODO-------
	//Texture
	//Color

};

