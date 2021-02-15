
#shader VERTEX
#version 330 core
layout(location = 0) in vec4 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 _MVP;

void main()
{
	gl_Position = _MVP * pos;
};

#shader FRAGMENT

#version 330 core
layout(location = 0) out vec4 outColor;

void main()
{
	outColor = vec4(1.0f);
}; 
