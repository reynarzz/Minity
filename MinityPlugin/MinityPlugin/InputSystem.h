#pragma once
#include "Scene.h"
#include "Unity_PluginAPI/IUnityInterface.h"


#include <gainput/gainput.h>
#include <gainput/GainputDebugRenderer.h>

using gainput::DebugRenderer;

//#include <Windows.h>
enum class NormalKey
{
	RELEASED = -1,
	NONE = 0,
	W = 1,
	A = 2,
	S = 3,
	D = 4,
	Q = 5,
	E = 6,
	F = 7,
	ENTER = 8,
	SPACE = 9,
};

enum class MouseKeys
{
	RELEASED = -1,
	NONE = 0,
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	Mid = 3
};

enum class ModifierKeys
{
	RELEASED = -1,
	NONE = 0,
	ALT = 1,
	SHIFT = 2
};

class InputSystem
{

public:
	// Use function pointers.
	class GAINPUT_LIBEXPORT DebugInput : public DebugRenderer
	{
	public:
		 ~DebugInput() override;

		 void DrawCircle(float x, float y, float radius) override;

		 void DrawLine(float x1, float y1, float x2, float y2) override;

		 void DrawText(float x, float y, const char* const text) override;
	};


	InputSystem(Camera* camera);
	void Update(float deltaTime);

private:
	DebugInput _debugInput;
};



