#pragma once
#include "MeshRenderer.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "ScreenInfo.h"

class MinityEngine
{
private:
	Renderer* _renderer;
	float _deltaTime;
	ScreenInfo _screenInfo;

public:
	MinityEngine();
	~MinityEngine();

	float GetDeltaTime();
	const ScreenInfo& GetScreenInfo();
	void Update(float deltaTime, const ScreenInfo& screenInfo);
};

