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

Renderer::Renderer(Camera* camera) : _camera(camera)
{
	if (glewInit() == GLEW_OK)
	{
		// Generate vertex array object
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
	}
}

void Renderer::SetCamera(Camera* camera)
{
	_camera = camera;
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

void Renderer::AddRendererToQueue(MeshRenderer* renderer)
{
	RenderingOrder order = renderer->GetMaterial()->_renderingOrder;

	CreateGroupIfEmpty(order, _renderers);
	_renderers[order]->push_back(renderer);
}

void Renderer::Draw()
{
	
	// Do proper ordering.
	for (auto rendererGroup : _renderers)
	{
		auto group = *rendererGroup.second;

		for (auto renderer : group)
		{
			renderer->Bind(_camera->GetViewProjMatrix());

			const Material* mat = renderer->GetMaterial();

			if (mat->_blending.enabled)
			{
				glEnable(GL_BLEND);
				glBlendFunc(mat->_blending._srcFactor, mat->_blending._dstFactor);
			}
			else
			{
				glDisable(GL_BLEND);
			}

			if (mat->_depthWrite)
			{
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);
				glDepthMask(GL_TRUE);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
				glDepthMask(GL_FALSE);
			}

			if (mat->culling._enabled)
			{
				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
				glCullFace(mat->culling.face);
			}
			else 
			{
				glDisable(GL_CULL_FACE);
			}

			Mesh* mesh = renderer->GetMesh();;

			glDrawElements(GL_TRIANGLES, mesh->GetIndices()->size(), GL_UNSIGNED_INT, 0);
		}
	}
}

// This should be listening to a object destruction. delegate event in destructor.
void Renderer::RemoveRenderer(MeshRenderer* renderer)
{
	Material* mat = renderer->GetMaterial();
	auto list = _renderers[mat->_renderingOrder];

	for (auto it = list->begin(); it != list->end(); it++)
	{
		if (renderer == *it._Unwrapped())
		{
			_renderers[mat->_renderingOrder]->erase(it);

			if (_renderers[mat->_renderingOrder]->size() == 0)
			{
				_renderers[mat->_renderingOrder]->clear();
			}
			break;
		}
	}
}


Renderer::~Renderer()
{
	_renderers.clear();
	//_renderers.shrink_to_fit();
}