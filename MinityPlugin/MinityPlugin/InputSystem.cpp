#include "pch.h"
#include "InputSystem.h"
#include "Unity_PluginAPI/IUnityInterface.h"

// Use function pointers.

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetPos(float x, float y, float z)
{
	//_pos = glm::vec3(x, y, z);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetRot(float x, float y, float z)
{
	//_rot = glm::vec3(x, y, z);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseData(float xPos, float yPos, float deltaX, float deltaY)
{
	/*_mousePos = glm::vec2(xPos, yPos);
	_mouseDelta = glm::vec2(deltaX, deltaY);*/
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyDow(int keyType, int key)
{
	/*if (keyType == 0)
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
	}*/
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyUp(int keyType)
{
	/*if (keyType == 0)
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
	}*/
}