#include "pch.h"

#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) :
	_mesh(mesh), _material(material), _vbo(-1), _ibo(-1)
{
}

Mesh* MeshRenderer::GetMesh() const
{
	return _mesh;
}

Material* MeshRenderer::GetMaterial() const
{
	return _material;
}

void MeshRenderer::Init()
{
	// Vertex Buffer
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _mesh->GetVertices()->size(), &_mesh->GetVertices()->at(0), GL_STREAM_DRAW);

	// Elements
	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _mesh->GetIndices()->size(), &_mesh->GetIndices()->at(0), GL_STREAM_DRAW);

	//_material->BindTextures();
}

void MeshRenderer::Bind(Camera* camera)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * _mesh->GetVertices()->size(), &_mesh->GetVertices()->at(0));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * _mesh->GetIndices()->size(), &_mesh->GetIndices()->at(0));

	unsigned int stride = sizeof(float) * 8;

	// Set vertex layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, stride, 0);
	glEnableVertexAttribArray(0);

	// Texture layout
	glVertexAttribPointer(1, 2, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// Normals layout
	glVertexAttribPointer(2, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);
	
	_material->UseMaterial(camera);
}

MeshRenderer::~MeshRenderer()
{
	delete _mesh, _material;
}