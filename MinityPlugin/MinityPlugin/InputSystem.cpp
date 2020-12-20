#include "pch.h"

#include "InputSystem.h"

// Use function pointers.

NormalKey _normalKey;
MouseKeys _mouseKey;
ModifierKeys _modifierKey;
glm::vec2 _mouseDelta;
glm::vec3 _position;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseData(float xPos, float yPos, float deltaX, float deltaY)
{
	//_mousePos = glm::vec2(xPos, yPos);
	_mouseDelta = glm::vec2(deltaX, deltaY);
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

InputSystem::InputSystem(Camera* camera)
{
	//This is bad
	_camera = camera;
}

void InputSystem::Update()
{
	if (_normalKey == NormalKey::A)
	{
		_position -= _camera->_right * 0.05f;
	}
	else if (_normalKey == NormalKey::D)
	{
		_position += _camera->_right * 0.05f;
	}

	if (_normalKey == NormalKey::W)
	{
		_position += _camera->_forward * 0.05f;
	}
	if (_normalKey == NormalKey::S)
	{
		_position -= _camera->_forward * 0.05f;
	}

	if (_normalKey == NormalKey::Q)
	{
		_position += glm::vec3(0.0f, -0.01f, 0.0f);
	}
	else if (_normalKey == NormalKey::E)
	{
		_position += glm::vec3(0.0f, 0.01f, 0.0f);
	}

	_camera->SetCameraPosition(_position);
	_camera->SetCameraRotation(_mouseDelta);
}