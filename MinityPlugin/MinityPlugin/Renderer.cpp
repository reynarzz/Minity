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

bool _glewInit;

Renderer::Renderer()
{
	if (glewInit() == GLEW_OK)
	{
		_glewInit = true;
	}
	else
	{
		_glewInit = false;
	}
}

Renderer::~Renderer()
{
	for (auto renderers : _renderers)
	{
		delete renderers;
	}
}

void Renderer::AddObjectToRenderer(MeshRenderer* meshRenderer)
{
	//glDisable(GL_CULL_FACE);
			//glDisable(GL_BLEND);

			//glDepthFunc(GL_LEQUAL);
			//glDepthMask(GL_FALSE);

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

	/*glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);*/
	//glEnable(GL_DEPTH_TEST);

	//glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	unsigned int vao;

	//Generate vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/*for (auto renderer : _renderers)
	{

	}*/

	MeshRenderer* renderer = _renderers[0];
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

	//Debug::Log(shaderProgram);


	//--unsigned int uniformModelID = glGetUniformLocation(shaderProgram, "model");
	//--unsigned int uniformProjectionID = glGetUniformLocation(shaderProgram, "project");

	//--glUniformMatrix4fv(uniformModelID, 1, GL_FALSE, glm::value_ptr(model));
	//--glUniformMatrix4fv(uniformProjectionID, 1, GL_FALSE, glm::value_ptr(projection));

	
	glDrawElements(GL_TRIANGLES, mesh->GetIndices()->size(), GL_UNSIGNED_INT, 0);

	glDeleteVertexArrays(1, &vao);
}
