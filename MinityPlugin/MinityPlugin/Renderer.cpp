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
	//Aqui es donde se dibuja,
	//Render estate: glDepthFunc(GL_LEQUAL);
	//Uso el shader program.
	//se setea el vertex array object si se esta usando el core profile. (siempre se esta usando)

	//glClear(GL_DEPTH_BUFFER_BIT);
	//glDepthRangef(0.1f, 100.0f);

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//DepthMask needs to be true!
	glDepthMask(GL_TRUE);

	//gluPerspective(45.0f, _mainCam->GetAspectRatio(), 0.1f, 500.0f);

	unsigned int vao;

	//Generate vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (auto rendererObj : _renderers)
	{
		MeshRenderer* renderer = rendererObj;
		Mesh* mesh = renderer->GetMesh();
		Material* material = renderer->GetMaterial();

		Shader* shader = material->GetShader();

		// Bind buffer and set data.
		glBindBuffer(GL_ARRAY_BUFFER, renderer->_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * mesh->GetVertices()->size(), &mesh->GetVertices()->at(0));

		// Set data layout for the shader.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->_ibo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * mesh->GetIndices()->size(), &mesh->GetIndices()->at(0));

		unsigned int shaderProgram = shader->BuildShader();

		glUseProgram(shaderProgram);

		SetShader_MVP_MATRIX(shaderProgram);

		//Debug::Log(shaderProgram);

		glDrawElements(GL_TRIANGLES, mesh->GetIndices()->size(), GL_UNSIGNED_INT, 0);

	}
	glDeleteVertexArrays(1, &vao);
}

float angle = 0.0f;

void Renderer::SetShader_MVP_MATRIX(unsigned int shaderProgram)
{
	unsigned int uniformModelID = glGetUniformLocation(shaderProgram, "model");
	unsigned int uniformViewID = glGetUniformLocation(shaderProgram, "view");
	unsigned int uniformProjectionID = glGetUniformLocation(shaderProgram, "projection");

	vector<Camera*> cameras = _scene->GetCameras();

	Camera* mainCamera = cameras.at(0);

	glm::mat4 modelTest(1.0f);

	angle += 0.20f;

	modelTest = glm::translate(modelTest, glm::vec3(0.0f, 0.0f, -5.0f));
	//modelTest = glm::rotate(modelTest, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(uniformModelID, 1, GL_FALSE, glm::value_ptr(modelTest));
	glUniformMatrix4fv(uniformViewID, 1, GL_FALSE, glm::value_ptr(mainCamera->GetViewMatrix()));
	glUniformMatrix4fv(uniformProjectionID, 1, GL_FALSE, glm::value_ptr(mainCamera->GetProjectionMatrix()));
}

Renderer::~Renderer()
{
	// Be carefull, clear deletes all.
	_renderers.clear();
	_renderers.shrink_to_fit();
}