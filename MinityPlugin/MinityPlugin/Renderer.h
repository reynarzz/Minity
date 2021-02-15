#pragma once
#include "Scene.h"
#include <map>

using std::vector;
using std::map;

class Renderer
{
private:
	Scene* _scene;
	//vector<MeshRenderer*> _renderers;
	//map<RenderingOrder, map<int, vector<MeshRenderer*>>> _renderers;
	map<int, vector<MeshRenderer*>*> _renderers;
public:
	Renderer(Scene* scene);
	~Renderer();

	void SetScene(Scene* scene);
	void AddRendererToQueue(MeshRenderer* renderer, RenderingOrder order);
	void Draw();
};

