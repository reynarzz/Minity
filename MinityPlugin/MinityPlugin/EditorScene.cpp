#include "pch.h"
#include "EditorScene.h"

//void MoveCamera()
//{
//	unsigned int viewUniformID = glGetUniformLocation(_shaderProgram, "view");
//
//	if (_mouseKey == MouseKeys::LEFT_CLICK)
//	{
//		_angleX += -_mouseDelta.y;
//		_angleY += _mouseDelta.x;
//	}
//
//	glm::vec3 forward(0.0f, 0.0f, -1.0f);
//
//	forward.x = cos(glm::radians(_angleY)) * cos(glm::radians(_angleX));
//	forward.y = sin(glm::radians(_angleX));
//	forward.z = sin(glm::radians(_angleY)) * cos(glm::radians(_angleX));
//
//	forward = glm::normalize(forward);
//
//	glm::vec3 right(glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0, 0.0f))));
//	glm::vec3 up(glm::normalize(glm::cross(right, forward)));
//
//	if (_normalKey == NormalKey::A)
//	{
//		right *= 0.01f;
//
//		position += -right;
//
//	}
//	else if (_normalKey == NormalKey::D)
//	{
//		right *= 0.01f;
//
//		position += right;
//	}
//
//	if (_normalKey == NormalKey::W)
//	{
//		forward *= 0.01f;
//
//		position += forward;
//	}
//	if (_normalKey == NormalKey::S)
//	{
//		forward *= 0.01f;
//
//		position += -forward;
//	}
//
//	if (_normalKey == NormalKey::Q) 
//	{
//		position += glm::vec3(0.0f, -0.01f, 0.0f);
//	}
//	else if (_normalKey == NormalKey::E)
//	{
//		position += glm::vec3(0.0f, 0.01f, 0.0f);
//	}
//
//	glm::mat4 view = glm::lookAt(position, position + forward, up);
//
//
//	glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, glm::value_ptr(view));
//}
