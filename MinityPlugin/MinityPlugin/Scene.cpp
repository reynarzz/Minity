#include "pch.h"
#include "GameEntity.h"

#include "Scene.h"

Scene::Scene()
{
	// I have to remove this later. An scene is able to exist without camera.
	_cameras.push_back(new Camera(glm::vec3(.0f, .0f, .0f), glm::vec2(-363, 220), 0));
}

void Scene::Update(ScreenInfo screenInfo, float deltaTime)
{
	for (auto camera : _cameras)
	{
		if (_screenInfo._dimensions.x != screenInfo._dimensions.x)
		{
			_screenInfo._dimensions.x = screenInfo._dimensions.x;

			camera->OnScreenSizeChanged(screenInfo._dimensions.x, screenInfo._dimensions.y);
			//Debug::Log("Size changed");
		}

		camera->Update(deltaTime);
	}
}

void Scene::AddGameEntity(GameEntity* gameEntity) 
{
	_gameEntities.push_back(gameEntity);
}

void Scene::RemoveGameEntity(GameEntity* gameEntity)
{
	// TODO
}

vector<MeshRenderer*> Scene::GetMeshRenderers()
{
	vector<MeshRenderer*> renderers;

	// slow
	for (auto gameEntities : _gameEntities)
	{
		MeshRenderer* renderer = gameEntities->GetComponent<MeshRenderer>();

		if (renderer != nullptr)
		{
			renderers.push_back(renderer);
		}
	}

	return renderers;
}

const vector<Camera*>& Scene::GetCameras() const
{
	return _cameras;
}

Scene::~Scene()
{
	// Clear destroys the objects!
	_gameEntities.clear();
	_gameEntities.shrink_to_fit();
}