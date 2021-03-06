#include "pch.h"
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "xinput.lib")
#include "InputSystem.h"

// Define your user buttons somewhere global
enum Button
{
	ButtonConfirm,
	Jump,

};
gainput::InputMap* _map;
gainput::InputManager* _manager;
gainput::DeviceId _keyboard;
gainput::MappedInputListener _listener;

bool created = false;

//InputSystem::InputSystem() // this should have the screen class 
//{
//	
//	//_map(_manager);
//}
// Use function pointers.

NormalKey _normalKey;
MouseKeys _mouseKey;
ModifierKeys _modifierKey;
glm::vec2 _mouseDelta;
glm::vec3 _position = glm::vec3(12.0f, 11.0f, 14.0f);
Camera* _camera;

float _i_moveSpeed;
 
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseData(float xPos, float yPos, float deltaX, float deltaY)
{
	//_mousePos = glm::vec2(xPos, yPos);
	_mouseDelta = glm::vec2(deltaX, deltaY);
	/*Debug::Log("Delta x");
	Debug::Log(deltaX);*/
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

void InputSystem::DebugInput::DrawCircle(float x, float y, float radius) 
{
	
}

void InputSystem::DebugInput::DrawLine(float x1, float y1, float x2, float y2)
{

}

void InputSystem::DebugInput::DrawText(float x, float y, const char* const text)
{
	Debug::Log(text);
}

InputSystem::DebugInput::~DebugInput() 
{
	
}

//void InputSystem::Update(float deltaTime)
//{
//	if (!created) 
//	{
//		created = true;
//
//		_manager = new gainput::InputManager(false);
//		_manager->SetDebugRenderer(&_debugInput);
//		_manager->SetDebugRenderingEnabled(true);
//
//		// Setting up Gainput
//		_keyboard = _manager->CreateDevice<gainput::InputDeviceKeyboard>();
//		_manager->CreateDevice<gainput::InputDevicePad>();
//
//		_manager->CreateDevice<gainput::InputDeviceMouse>();
//		_manager->SetDisplaySize(500, 500);
//
//		_map = new gainput::InputMap(*_manager);
//
//		if (_map->MapBool(ButtonConfirm, _keyboard, gainput::PadButtonA))
//		{
//
//		}
//
//		_map->MapBool(Jump, _keyboard, gainput::KeySpace);
//
//	} 
//
//	// Call every frame
//	_manager->Update(deltaTime);
//	// May have to call platform-specific event-handling functions here.
//	// Check button state
//}