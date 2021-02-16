#pragma once
#include "Scene.h"
#include <map>

using std::vector;
using std::map;

class Renderer
{
private:
	unsigned int _vao;
	Camera* _camera;
	//vector<MeshRenderer*> _renderers;
	//map<RenderingOrder, map<int, vector<MeshRenderer*>>> _renderers;
	map<int, vector<MeshRenderer*>*> _renderers;
public:
	Renderer(Camera* camera);
	~Renderer();

	void SetCamera(Camera* camera);
	void AddRendererToQueue(MeshRenderer* renderer);
	void RemoveRenderer(MeshRenderer* renderer);
	void Draw();
};

