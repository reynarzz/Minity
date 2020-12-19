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
	_projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 150.0f);
	//mat4 projection = glm::perspective(45.0f, _screenAspectRatio, 0.1f, 150.0f);
}

const mat4& Camera::GetViewMatrix(vec3 cameraPos, vec2 mouseDelta)
{
	_cameraPos = cameraPos;

	_cameraRot.x += -mouseDelta.y;
	_cameraRot.y += mouseDelta.x;

	glm::vec3 forward(0.0f, 0.0f, -1.0f);

	forward.x = cos(glm::radians(_cameraRot.y)) * cos(glm::radians(_cameraRot.x));
	forward.y = sin(glm::radians(_cameraRot.x));
	forward.z = sin(glm::radians(_cameraRot.y)) * cos(glm::radians(_cameraRot.x));

	forward = glm::normalize(forward);

	glm::vec3 right(glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0, 0.0f))));
	glm::vec3 up(glm::normalize(glm::cross(right, forward)));

	_viewMatrix = glm::lookAt(_cameraPos, _cameraPos + forward, up);

	return _viewMatrix;
}

const mat4& Camera::GetProjectionMatrix() const
{
	return _projectionMatrix;
}

Camera::~Camera()
{

}