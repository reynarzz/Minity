#include "pch.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/type_trait.hpp>

#include <vector>
#include "MeshRenderer.h"

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

#include "Renderer.h"

bool _glewInit;
Camera* _mainCam;

Renderer::Renderer(Scene* startScene) : _scene(startScene)
{
	if (glewInit() == GLEW_OK)
	{
		_glewInit = true;
	}
	else
	{
		_glewInit = false;
	}

	SetScene(startScene);
}

void Renderer::SetScene(Scene* scene)
{
	_scene = scene;

	auto meshRenderers = scene->GetMeshRenderers();

	unsigned int vao;

	//Generate vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (MeshRenderer* meshRenderer : meshRenderers)
	{
		meshRenderer->Init();
		_renderers.push_back(meshRenderer);
	}

	_mainCam = _scene->GetCameras().at(0);
}

void Renderer::Draw()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_TRUE);

	for (auto renderer : _renderers)
	{
		renderer->Bind(_mainCam);

		Mesh* mesh = renderer->GetMesh();
		//glDrawArrays(GL_POINTS, 0, mesh->GetVertices()->size());

		glDrawElements(GL_TRIANGLES, mesh->GetIndices()->size(), GL_UNSIGNED_INT, 0);
	}
}

Renderer::~Renderer()
{
	_renderers.clear();
	_renderers.shrink_to_fit();
}