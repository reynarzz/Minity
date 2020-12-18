#include "pch.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/type_trait.hpp>

#include <vector>
#include "MeshRenderer.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

unsigned int _vao;

Renderer::Renderer()
{
	glewInit();
}

Renderer::~Renderer()
{
	for (auto renderers : _renderers)
	{
		delete renderers;
	}
}

void Renderer::AddMeshToRenderer(MeshRenderer* meshRenderer)
{
	//glDisable(GL_CULL_FACE);
			//glDisable(GL_BLEND);

			//glDepthFunc(GL_LEQUAL);
			//glDepthMask(GL_FALSE);

	Mesh* mesh = meshRenderer->GetMesh();
	Material* material = meshRenderer->GetMaterial();

	glGenBuffers(1, &meshRenderer->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, meshRenderer->_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->GetVertices()->size(), mesh->GetVertices(), GL_STREAM_DRAW);


	glGenBuffers(1, &meshRenderer->_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshRenderer->_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->GetIndices()->size(), mesh->GetIndices(), GL_STREAM_DRAW);

	_renderers.push_back(meshRenderer);
}

void Renderer::Draw()
{
	//Aqui es donde se dibuja,
	//Render estate: glDepthFunc(GL_LEQUAL);
	//Uso el shader program.
	//se setea el vertex array object si se esta usando el core profile. (siempre se esta usando)

	/*glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);*/
	//glEnable(GL_DEPTH_TEST);

	//glClear(GL_DEPTH_BUFFER_BIT);

	//Generate vertex array object
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	/*for (auto renderer : _renderers)
	{

	}*/

	MeshRenderer* renderer = _renderers[0];
	Mesh* mesh = renderer->GetMesh();
	Material* material = renderer->GetMaterial();

	auto shader = material->GetShader();
	int verticesCount = mesh->GetVertices()->size();
	int indicesCount = mesh->GetIndices()->size();

	// Bind buffer and set data.
	glBindBuffer(GL_ARRAY_BUFFER, renderer->_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * verticesCount, mesh->GetVertices());

	// Set data layout for the shader.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->_ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * indicesCount, mesh->GetIndices());

	unsigned int shaderProgram = shader->BuildShader();

	glUseProgram(shaderProgram);

	//--unsigned int uniformModelID = glGetUniformLocation(shaderProgram, "model");
	//--unsigned int uniformProjectionID = glGetUniformLocation(shaderProgram, "project");

	//--glUniformMatrix4fv(uniformModelID, 1, GL_FALSE, glm::value_ptr(model));
	//--glUniformMatrix4fv(uniformProjectionID, 1, GL_FALSE, glm::value_ptr(projection));

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

	glDeleteVertexArrays(1, &_vao);
}
