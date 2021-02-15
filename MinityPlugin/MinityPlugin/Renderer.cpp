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
#include <iostream>

bool _glewInit;
Camera* _mainCam;

Renderer::Renderer(Scene* startScene) : _scene(startScene)
{
	if (glewInit() == GLEW_OK)
	{
		_glewInit = true;

		SetScene(startScene);
	}
	else
	{
		_glewInit = false;
	}
}

void Renderer::SetScene(Scene* scene)
{
	_scene = scene;

	auto meshRenderers = scene->GetMeshRenderers();

	unsigned int vao;

	// Generate vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (MeshRenderer* meshRenderer : meshRenderers)
	{
		meshRenderer->Init();

		AddRendererToQueue(meshRenderer, meshRenderer->GetMaterial()->_renderingOrder);

		//_renderers.push_back(meshRenderer);
	}

	_mainCam = _scene->GetCameras().at(0);
}

void CreateGroupIfEmpty(int order, map<int, vector<MeshRenderer*>*>& renderers)
{
	vector<MeshRenderer*>* renders = new vector<MeshRenderer*>();
	bool contains = renderers.count(order) > 0;

	if (!contains)
	{
		renderers.insert(std::make_pair(order, renders));
	}
}

void Renderer::AddRendererToQueue(MeshRenderer* renderer, RenderingOrder order)
{
	CreateGroupIfEmpty(order, _renderers);

	_renderers[order]->push_back(renderer);
}

void Renderer::Draw()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_TRUE);

	// Do proper ordering.
	for (auto rendererGroup : _renderers)
	{
		auto group = *rendererGroup.second;

		for (auto renderer : group)
		{
			renderer->Bind(_mainCam);
			const Material* mat = renderer->GetMaterial();
			
			// Testing: Alpha blending, i need a Queuing system.
			if (mat->_srcFactor != 0 && mat->_dstFactor != 0) 
			{
				glEnable(GL_BLEND);
				glBlendFunc(mat->_srcFactor, mat->_dstFactor);
			}
			else 
			{
				glDisable(GL_BLEND);
			}

			if (renderer->DepthWrite())
			{
				glEnable(GL_DEPTH_TEST);
				glDepthMask(GL_TRUE);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
				glDepthMask(GL_FALSE);
			}

			Mesh* mesh = renderer->GetMesh();;

			glDrawElements(GL_TRIANGLES, mesh->GetIndices()->size(), GL_UNSIGNED_INT, 0);
		}
	}
}

Renderer::~Renderer()
{
	_renderers.clear();
	//_renderers.shrink_to_fit();
}