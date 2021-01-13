#include "pch.h"

#include "InputSystem.h"

// Use function pointers.

NormalKey _normalKey;
MouseKeys _mouseKey;
ModifierKeys _modifierKey;
glm::vec2 _mouseDelta;
glm::vec3 _position;
float _i_moveSpeed;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseData(float xPos, float yPos, float deltaX, float deltaY)
{
	//_mousePos = glm::vec2(xPos, yPos);
	_mouseDelta = glm::vec2(deltaX, deltaY);
	Debug::Log(deltaX);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyDow(int keyType, int key)
{
	if (keyType == 0)
	{
		_normalKey = static_cast<NormalKey>(key);
	}
	if (keyType == 1)
	{
		_mouseKey = static_cast<MouseKeys>(key);
	}
	else if (keyType == 2)
	{
		_modifierKey = static_cast<ModifierKeys>(key);
	}

	if (keyType > 2)
	{
		Debug::Log("Wrong key number");
	}
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyUp(int keyType)
{
	if (keyType == 0)
	{
		_normalKey = NormalKey::RELEASED;
	}

	if (keyType == 1)
	{
		_mouseKey = MouseKeys::RELEASED;
	}

	if (keyType == 2)
	{
		_modifierKey = ModifierKeys::RELEASED;
	}

	if (keyType > 2)
	{
		Debug::Log("Wrong key number");
	}
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMoveSpeed(float speed)
{
	_i_moveSpeed = speed;
}

InputSystem::InputSystem(Camera* camera)
{
	//This is bad
	_camera = camera;
}

void InputSystem::Update(float deltaTime)
{
	if (_normalKey == NormalKey::A)
	{
		_position -= _camera->_right * _i_moveSpeed * deltaTime;
	}
	else if (_normalKey == NormalKey::D)
	{
		_position += _camera->_right * _i_moveSpeed * deltaTime;
	}

	if (_normalKey == NormalKey::W)
	{
		_position += _camera->_forward * _i_moveSpeed * deltaTime;
	}
	if (_normalKey == NormalKey::S)
	{
		_position -= _camera->_forward * _i_moveSpeed * deltaTime;
	}

	if (_normalKey == NormalKey::Q)
	{
		_position += glm::vec3(0.0f, -_i_moveSpeed, 0.0f) * deltaTime;
	}
	else if (_normalKey == NormalKey::E)
	{
		_position += glm::vec3(0.0f, _i_moveSpeed, 0.0f) * deltaTime;
	}

	_camera->SetCameraPosition(_position);
	_camera->SetCameraRotation(_mouseDelta);
}