#pragma once

using std::vector;

class Renderer
{
private:
	vector<MeshRenderer*> _renderers;
public:

	Renderer();
	~Renderer();

	void AddMeshToRenderer(MeshRenderer* mesh);

	void Draw();
};

