#include "pch.h"
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

void Scene::AddMeshRenderer(MeshRenderer* renderer) 
{
	_objects.push_back(renderer);
}

void Scene::RemoveMeshRenderer(MeshRenderer* renderer) 
{
	// TODO
}

const vector<MeshRenderer*>& Scene::GetMeshRenderers() const
{
	return _objects;
}

const vector<Camera*>& Scene::GetCameras() const
{
	return _cameras;
}

Scene::~Scene()
{
	// Clear destroys the objects!
	_objects.clear();
	_objects.shrink_to_fit();
}