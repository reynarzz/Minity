
#shader VERTEX
#version 330 core
layout(location = 0) in vec4 pos;

uniform mat4 _MVP;

void main()
{
	gl_Position = _MVP * pos;
};

#shader FRAGMENT

#version 330 core
layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0f,1.0f,1.0f,1.0f);
}; 