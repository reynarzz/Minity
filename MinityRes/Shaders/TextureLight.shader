#shader VERTEX
#version 330 core

layout(location = 0) in vec4 _pos;
layout(location = 1) in vec2 _uv;
layout(location = 2) in vec3 normal;

uniform mat4 _MVP;

out vec2 _uvCoord;

uniform sampler2D _texture;
out vec3 _normal;

void main() 
{
	_uvCoord = _uv;
	_normal = normal;
	gl_Position = _MVP * _pos;
}

#shader FRAGMENT

#version 330 core

out vec4 color;
in vec2 _uvCoord;
uniform sampler2D _texture;
vec3 lightDir;
in vec3 _normal;


uniform vec3 _diffuse_;
uniform float _alpha_;

void main() 
{
	lightDir = vec3(0.5, -0.3, -0.5);
	color = texture(_texture, _uvCoord) * (step(normalize(dot(_normal, lightDir)), 0.4) + 0.4) * vec4(_diffuse_, _alpha_);
}