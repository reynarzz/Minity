#pragma once
#include "MeshRenderer.h"
#include "Renderer.h"
#include "InputSystem.h"

class ScreenInfo
{
public:
	glm::vec2 _dimensions;
	float _aspectRatio;
};

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

