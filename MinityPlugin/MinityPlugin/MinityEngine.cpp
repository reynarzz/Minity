#include "pch.h"
#include "Unity_PluginAPI/IUnityInterface.h"

#include "MinityEngine.h"
#include "Scene.h"

Scene* _scene;
InputSystem* _inputSystem;
//Aqui inicializo el renderer de open gl (Creo los shaders, seteo las matrices(world y projection), crear los vertex buffer)

/// <summary>An engine that runs above the unity engine.</summary>
MinityEngine::MinityEngine()
	: _deltaTime(-1), _screenInfo()
{
	//I will have to remove this later
	_scene = new Scene();

	_renderer = new Renderer(_scene);

	_inputSystem = new InputSystem(_scene->GetCameras().at(0));
}

void MinityEngine::Update(float deltaTime, const ScreenInfo& screenInfo)
{
	_deltaTime = deltaTime;
	_screenInfo = screenInfo;

	// Do your stuff below.--------------
	_inputSystem->Update(deltaTime);
	_scene->Update(screenInfo, deltaTime);
	
	_renderer->Draw();
}

float MinityEngine::GetDeltaTime()
{
	return _deltaTime;
}

MinityEngine::~MinityEngine()
{
	delete _scene, _renderer, _inputSystem;
}