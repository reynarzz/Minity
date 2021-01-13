#pragma once
#include "Camera.h"
#include "MeshRenderer.h"

class Scene
{
private:
	vector<Camera*> _cameras;
	vector<MeshRenderer*> _objects;
public:
	Scene();
	~Scene();

	const vector<MeshRenderer*>& GetMeshRenderers() const;
	const vector<Camera*>& GetCameras() const;
	//mat4 model = glm::mat4(1.0f);

	//model = glm::translate(model, _pos);
	//model = glm::rotate(model, _time /* 3.14f / 180*/, glm::vec3(0.0f, 1.0f, 0.0f));
	void Update(float aspect, float deltaTime);
};

