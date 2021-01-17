
#shader VERTEX
#version 330 core
layout(location = 0) in vec4 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 posColor;

void main()
{
	gl_Position = projection * view * model * pos;
    posColor = pos;
};

#shader FRAGMENT

#version 330 core
out vec4 FragColor;

float near = 0.1;
float far = 10.0;

in vec4 posColor;

float LinearizeDepth(float depth)
{
    float z = (depth * 2.0 - 1.0); // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    FragColor = vec4(vec3(depth) * -1.0 + vec3(0.9f), 1.0);// * posColor;
}