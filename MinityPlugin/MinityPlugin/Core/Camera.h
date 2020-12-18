#pragma once
class Camera
{
private:
	mat4 _viewMatrix;
	vec3 _cameraPos;
	vec3 _cameraRot;
public:

	Camera(vec3 position, vec3 rotation);
	~Camera();

	void SetCameraMoveSpeed(float speed);
	void SetCameraPos(vec3 cameraPos);
	mat4 GetViewMatrix(vec3 cameraPos, vec2 mouseDelta);
};

