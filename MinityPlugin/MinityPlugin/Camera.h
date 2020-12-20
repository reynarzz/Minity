#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec2;

class Camera
{
private:
	mat4 _viewMatrix;
	vec3 _cameraPos;
	vec2 _cameraRot;
	mat4 _projectionMatrix;
	float _aspectRatio;

public:

	glm::vec3 _forward;
	glm::vec3 _right;
	glm::vec3 _up;

	Camera(vec3 position, vec2 rotation, float aspectRatio);
	~Camera();

	const mat4& GetViewMatrix();
	const mat4& GetProjectionMatrix() const;
	void UpdateProjectionMatrix(float aspectRatio);

	void SetCameraPosition(glm::vec3 pos);
	void SetCameraRotation(glm::vec2 mouseDelta);
	float GetAspectRatio() const;
};