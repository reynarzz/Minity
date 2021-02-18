#shader VERTEX
#version 330 core

layout(location = 0) in vec4 _pos;
layout(location = 1) in vec2 _uv;
layout(location = 2) in vec3 normal;

uniform mat4 _mvp_;

out vec2 _uvCoord;

uniform sampler2D _texture;
out vec3 _normal;

void main() 
{
	_uvCoord = _uv;
	_normal = normal;
	gl_Position = _mvp_ * _pos;
}

#shader FRAGMENT

#version 330 core

out vec4 color;
in vec2 _uvCoord;
uniform sampler2D _texture;
in vec3 _normal;

uniform vec3 _diffuse_; // from material
uniform float _alpha_; 	// from material

void main() 
{
	vec3 lightDir =  normalize(vec3(-0.5, 0.5, 0.5));

	float light = normalize(dot(_normal, lightDir));

	float flatC = step(0.4, light)  + 0.4;

	color = texture(_texture, _uvCoord) * light * vec4(_diffuse_, _alpha_);
}