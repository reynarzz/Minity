#include "pch.h"

#include "glm/matrix.hpp"
#include "glm/glm.hpp"
#include "Camera.h"
#include "DebugCPP.h"

float _angleX;
float _angleY;
float _xMove;
glm::vec2 _mouseDeltaCam;
glm::vec2 _inmmediateRot;
glm::vec3 _inmmediatePos;

float Lerp(float start, float end, float percent)
{
	return (start + percent * (end - start));
}


glm::vec3 Lerp(glm::vec3 start, glm::vec3 end, float percent)
{
	return (start + percent * (end - start));
}

glm::vec2 Lerp(glm::vec2 start, glm::vec2 end, float percent)
{
	return (start + percent * (end - start));
}

Camera::Camera(vec3 cameraPos, vec2 cameraRot, float aspectRatio)
	: _cameraPos(cameraPos), _cameraRot(cameraRot), _viewMatrix(mat4(1.0f))
{
	_aspectRatio = aspectRatio;
	_inmmediatePos = cameraPos;
	_inmmediateRot = cameraRot;
	_projectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);
}

const mat4& Camera::GetViewMatrix()
{
	return _viewMatrix;
}

const mat4& Camera::GetProjectionMatrix() const
{
	return _projectionMatrix;
}

void Camera::Update(float deltaTime)
{
	_forward = glm::vec3(0.0f, 0.0f, -1.0f);

	_inmmediateRot.x += -_mouseDeltaCam.y;
	_inmmediateRot.y += _mouseDeltaCam.x;

	_cameraRot = Lerp(_cameraRot, _inmmediateRot, deltaTime * 26.0f);

	_forward.x = cos(glm::radians(_cameraRot.y)) * cos(glm::radians(_cameraRot.x));
	_forward.y = sin(glm::radians(_cameraRot.x));
	_forward.z = sin(glm::radians(_cameraRot.y)) * cos(glm::radians(_cameraRot.x));

	_forward = glm::normalize(_forward);

	_right = glm::vec3(glm::normalize(glm::cross(_forward, glm::vec3(0.0f, 1.0, 0.0f))));
	_up = glm::vec3(glm::normalize(glm::cross(_right, _forward)));

	_cameraPos = _inmmediatePos;// Lerp(_cameraPos, _inmmediatePos, deltaTime * 10.0f);

	_viewMatrix = glm::lookAt(_cameraPos, _cameraPos + _forward, _up);

	_viewProjM = _projectionMatrix * _viewMatrix;
}
	
void Camera::SetCameraRotation(glm::vec2 mouseDelta)
{
	_mouseDeltaCam = mouseDelta;

}

void Camera::SetCameraPosition(glm::vec3 pos)
{
	_inmmediatePos = pos;
}

float Camera::GetAspectRatio() const
{
	return _aspectRatio;
}

mat4 Camera::GetViewProjMatrix() const
{
	return _viewProjM;
}

void Camera::OnScreenSizeChanged(float width, float height)
{
	// using perspective for now.
	_projectionMatrix = glm::perspective(45.0f, width/height, 0.1f, 1000.0f);
}

Camera::~Camera()
{

}