#pragma once

using std::vector;

class Renderer
{
private:
	vector<MeshRenderer*> _renderers;
public:

	Renderer();
	~Renderer();

	void AddObjectToRenderer(MeshRenderer* mesh);

	void Draw();
};

