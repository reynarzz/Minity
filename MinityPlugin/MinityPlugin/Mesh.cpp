#include "pch.h"

#include "Mesh.h"

Mesh::Mesh(vector<float>* vertices, vector<unsigned int>* indices):
	_vertices(vertices), _indices(indices)
{
}

void Mesh::SetVertices(vector<float>* vertices)
{
	_vertices = vertices;
}

void Mesh::SetIndices(vector<unsigned int>* indices)
{
	_indices = indices;
}

vector<float>* Mesh::GetVertices() const
{
	return _vertices;
}

vector<unsigned int>* Mesh::GetIndices() const
{
	return _indices;
}


Mesh::~Mesh()
{
	delete _vertices, _indices;
}
