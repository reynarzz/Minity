#pragma once
class Camera
{
private:
	mat4 _viewMatrix;
	vec3 _cameraPos;
	vec3 _cameraRot;
public:

	Camera();
	~Camera();

	mat4 MoveCamera(vec2 mouseDelta);
};

