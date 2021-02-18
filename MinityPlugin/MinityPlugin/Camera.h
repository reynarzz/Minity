#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ScreenInfo.h"

using glm::mat4;
using glm::vec3;
using glm::vec2;

class Camera// : Component
{
private:
	mat4 _viewMatrix;
	vec2 _cameraRot;
	mat4 _projectionMatrix;
	mat4 _viewProjM;
	float _aspectRatio;

public:
	vec3 _cameraPos;

	glm::vec3 _forward;
	glm::vec3 _right;
	glm::vec3 _up;

	Camera(vec3 position, vec2 rotation, float aspectRatio);
	~Camera();

	const mat4& GetViewMatrix();
	const mat4& GetProjectionMatrix() const;
	void Update(float deltaTime);

	void SetCameraPosition(glm::vec3 pos);
	void SetCameraRotation(glm::vec2 mouseDelta);
	float GetAspectRatio() const;
	mat4 GetViewProjMatrix() const;
	void OnScreenSizeChanged(float width, float height);
};