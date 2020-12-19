#pragma once
#include "Scene.h"

using std::vector;

class Renderer
{
private:
	Scene* _scene;
	vector<MeshRenderer*> _renderers;
	void AddMeshRendererToRenderer(MeshRenderer*);
	void SetShader_MVP_MATRIX(unsigned int shaderProgram);
public:
	Renderer(Scene* scene);
	~Renderer();

	void SetScene(Scene* scene);

	void Draw();
};

