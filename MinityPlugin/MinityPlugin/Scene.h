#pragma once
#include "Camera.h"
#include "MeshRenderer.h"
#include "ScreenInfo.h"
#include "GameEntity.h"

class Scene
{
private:
	string name;
	vector<Camera*> _cameras;
	vector<GameEntity*> _gameEntities;
	ScreenInfo _screenInfo;
public:
	Scene();
	~Scene();

	vector<MeshRenderer*> GetMeshRenderers();
	const vector<Camera*>& GetCameras() const;

	void AddGameEntity(GameEntity* entity);
	void RemoveGameEntity(GameEntity* entity);

	//mat4 model = glm::mat4(1.0f);

	//model = glm::translate(model, _pos);
	//model = glm::rotate(model, _time /* 3.14f / 180*/, glm::vec3(0.0f, 1.0f, 0.0f));
	void Update(ScreenInfo screenInfo, float deltaTime);
};

