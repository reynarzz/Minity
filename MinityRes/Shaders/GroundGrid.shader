#shader VERTEX

#version 330 core

layout(location = 0) in vec4 _pos;
layout(location = 1) in vec2 _uvIn;

out vec2 _uv;

uniform mat4 _mvp_;
out vec3 _pixelPos;

void main()
{
    _uv = _uvIn;
    _pixelPos = _pos.xyz;
	gl_Position = _mvp_ * _pos;
}

#shader FRAGMENT

#version 330 core

in vec2 _uv;
uniform vec3 _diffuse_;
out vec4 color;
uniform vec3 _cameraWorldPos_; 
in vec3 _pixelPos;
void main()
{
	float maxDist = 100;
	int pixelCoord = _uv * vec2(600, 400);

	//float alpha = (maxDist - length(_pixelPos - _cameraWorldPos_)) * mod(floor(_uv.x * 500) + floor(_uv.y * 500) , 2.);
 	float alpha = pixelCoord.x / maxDist;
	color = vec4(_diffuse_, smoothstep(0.0, 0.3, (smoothstep(0.0, 0.3, alpha)); 
}