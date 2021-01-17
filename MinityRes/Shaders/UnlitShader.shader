
#shader VERTEX
#version 330 core
layout(location = 0) in vec4 pos;

out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	color = pos;
	gl_Position = projection * view * model * pos;
	//gl_Position = pos;
};

#shader FRAGMENT

#version 330 core
layout(location = 0) out vec4 outColor;
in vec4 color;

void main()
{
	outColor = color * gl_FragCoord.z;//vec4(1.0f,1.0f,1.0f,1.0f);
}; 
