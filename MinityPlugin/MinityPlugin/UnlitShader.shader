
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



//#shader VERTEX
//#version 330 core
//layout(location = 0) in vec4 pos;
//
//out vec4 color;
//
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//
//void main()
//{
//	color = pos;
//	gl_Position = projection * view * model * pos;
//	gl_TexCoord[0] = gl_MultiTexCoord0;
//	//gl_Position = pos;
//};
//
//#shader FRAGMENT
//
//#version 330 core
//layout(location = 0) out vec4 outColor;
//in vec4 color;
//
//uniform sampler2D sceneSampler; // 0
//uniform sampler2D depthSampler; // 1
//
//float LinearizeDepth(vec2 uv)
//{
//	float n = 1.0; // camera z near
//	float f = 100.0; // camera z far
//	float z = texture2D(depthSampler, uv).x;
//	return (2.0 * n) / (f + n - z * (f - n));
//}
//
//void main()
//{
//	vec2 uv = gl_TexCoord[0].xy;
//	//vec4 sceneTexel = texture2D(sceneSampler, uv);
//	float d;
//	if (uv.x < 0.5) // left part
//		d = LinearizeDepth(uv);
//	else // right part
//		d = texture2D(depthSampler, uv).x;
//
//	outColor = vec4(d, d, d, 1.0);
//};