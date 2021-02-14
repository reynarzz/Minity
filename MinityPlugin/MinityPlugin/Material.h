#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>

class Material
{
public:
	struct MatAttribs 
	{
	public:
		std::string name;

		// 3 element array
		float* ambient;
		float* diffuse;
		float* specular;
		float* transmittance;
		float* emission;

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

