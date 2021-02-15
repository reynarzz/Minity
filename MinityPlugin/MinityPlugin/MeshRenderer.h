#pragma once

#include "Mesh.h"
#include "Material.h"

class MeshRenderer
{
private:
	
	Material* _material;
	Mesh* _mesh;
	
public:
	
	/// <summary>Vertex buffer obj.</summary>
	unsigned int _vbo;
	/// <summary>Index buffer obj.</summary>
	unsigned int _ibo;
	MeshRenderer(Mesh* mesh, Material* material);
	~MeshRenderer();

	Mesh* GetMesh() const;
	Material* GetMaterial() const;
	void Init();
	void Bind(Camera* camera);
	bool AlphaBlend() const;
};