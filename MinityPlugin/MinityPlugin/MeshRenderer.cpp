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

MeshRenderer::~MeshRenderer() 
{
	delete _mesh, _material;
}