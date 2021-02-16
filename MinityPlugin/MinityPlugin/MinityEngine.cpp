#include "pch.h"
#include "Unity_PluginAPI/IUnityInterface.h"

#include "MinityEngine.h"
#include "Scene.h"
#include "MeshSendToSceneTest.h"

Scene* _scene;
InputSystem* _inputSystem;

float timeToDestroy;

void SendRenders_Test(Renderer* renderer, Scene* scene)
{
	for (auto meshRenderer : scene->GetMeshRenderers())
	{
		meshRenderer->Init();

		Material* mat = meshRenderer->GetMaterial();

		if (meshRenderer->GetMaterial()->GetMatAttribs().dissolve < 0.9999f)
		{
			mat->_renderingOrder = RenderingOrder::Transparent;

			mat->_blending.enabled = true;
			mat->_blending._srcFactor = GL_SRC_ALPHA;
			mat->_blending._dstFactor = GL_ONE_MINUS_SRC_ALPHA;
			mat->culling._enabled = false;
		}
		else 
		{
			mat->culling._enabled = true;
			mat->culling.face = GL_BACK;
		}

		renderer->AddRendererToQueue(meshRenderer);
	}
}

//Aqui inicializo el renderer de open gl (Creo los shaders, seteo las matrices(world y projection), crear los vertex buffer)
/// <summary>An engine that runs above the unity engine.</summary>
MinityEngine::MinityEngine()
	: _deltaTime(-1), _screenInfo()
{
	//I will have to remove this later
	_scene = new Scene();

	MeshSendToSceneTest loadMeshTest;
	loadMeshTest.SetMeshRenderersToScene(_scene);

	_renderer = new Renderer(_scene->GetCameras().at(0));

	_inputSystem = new InputSystem(_scene->GetCameras().at(0));

	SendRenders_Test(_renderer, _scene);
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