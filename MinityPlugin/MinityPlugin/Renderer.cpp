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

	for (MeshRenderer* meshRenderer : meshRenderers)
	{
		AddMeshRendererToRenderer(meshRenderer);
	}

	_mainCam = _scene->GetCameras().at(0);
}

// Move to another place
void Renderer::AddMeshRendererToRenderer(MeshRenderer* meshRenderer)
{
	Mesh* mesh = meshRenderer->GetMesh();
	Material* material = meshRenderer->GetMaterial();

	glGenBuffers(1, &meshRenderer->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, meshRenderer->_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->GetVertices()->size(), &mesh->GetVertices()->at(0), GL_STREAM_DRAW);

	glGenBuffers(1, &meshRenderer->_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshRenderer->_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->GetIndices()->size(), &mesh->GetIndices()->at(0), GL_STREAM_DRAW);

	_renderers.push_back(meshRenderer);
}

void Renderer::Draw()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_TRUE);

	unsigned int vao;

	//Generate vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (auto renderer : _renderers)
	{
		Mesh* mesh = renderer->GetMesh();
		Material* material = renderer->GetMaterial();

		Shader* shader = material->GetShader();

		// Bind buffer and set data.
		glBindBuffer(GL_ARRAY_BUFFER, renderer->_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * mesh->GetVertices()->size(), &mesh->GetVertices()->at(0));

		// Set data layout for the shader.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->_ibo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * mesh->GetIndices()->size(), &mesh->GetIndices()->at(0));

		material->UseMaterial(_mainCam);

		//Debug::Log(shaderProgram);
		glDrawElements(GL_TRIANGLES, mesh->GetIndices()->size(), GL_UNSIGNED_INT, 0);
	}
	glDeleteVertexArrays(1, &vao);
}

Renderer::~Renderer()
{
	_renderers.clear();
	_renderers.shrink_to_fit();
}