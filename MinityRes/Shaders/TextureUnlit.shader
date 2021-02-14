#shader VERTEX
#version 330 core

layout(location = 0) in vec4 _pos;
layout(location = 1) in vec2 _uv;

uniform mat4 _MVP;

out vec2 _uvCoord;

uniform sampler2D _texture;

void main() 
{
	_uvCoord = _uv;
	gl_Position = _MVP * _pos;
}

#shader FRAGMENT

#version 330 core

out vec4 color;
in vec2 _uvCoord;
uniform sampler2D _texture;

void main() 
{
	color = texture(_texture, _uvCoord) * vec4(1.0);
}