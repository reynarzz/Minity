#include "pch.h"

#include "glm/matrix.hpp"
#include "glm/glm.hpp"
#include "Camera.h"

float _angleX;
float _angleY;
float _xMove;

Camera::Camera(vec3 cameraPos, vec2 cameraRot, float aspectRatio)
	: _cameraPos(cameraPos), _cameraRot(cameraRot), _viewMatrix(mat4(1.0f))
{
	_aspectRatio = aspectRatio;

	_projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 10.0f);
	//mat4 projection = glm::perspective(45.0f, _screenAspectRatio, 0.1f, 150.0f);
}

const mat4& Camera::GetViewMatrix()
{
	_forward = glm::vec3(0.0f, 0.0f, -1.0f);

	_forward.x = cos(glm::radians(_cameraRot.y)) * cos(glm::radians(_cameraRot.x));
	_forward.y = sin(glm::radians(_cameraRot.x));
	_forward.z = sin(glm::radians(_cameraRot.y)) * cos(glm::radians(_cameraRot.x));

	_forward = glm::normalize(_forward);

	_right = glm::vec3(glm::normalize(glm::cross(_forward, glm::vec3(0.0f, 1.0, 0.0f))));
	_up = glm::vec3(glm::normalize(glm::cross(_right, _forward)));

	_viewMatrix = glm::lookAt(_cameraPos, _cameraPos + _forward, _up);

	return _viewMatrix;
}

const mat4& Camera::GetProjectionMatrix() const
{
	return _projectionMatrix;
}

void Camera::UpdateProjectionMatrix(float aspectRatio)
{
	_aspectRatio = aspectRatio;
	_projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 10.0f);
}

void Camera::SetCameraRotation(glm::vec2 mouseDelta)
{
	_cameraRot.x += -mouseDelta.y;
	_cameraRot.y += mouseDelta.x;
}

void Camera::SetCameraPosition(glm::vec3 pos)
{
	_cameraPos = pos;
}

float Camera::GetAspectRatio() const 
{
	return _aspectRatio;
}

Camera::~Camera()
{

}