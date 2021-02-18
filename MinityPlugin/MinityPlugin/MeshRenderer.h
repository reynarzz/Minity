#pragma once

#include "Mesh.h"
#include "Material.h"
#include "GameComponent.h"
#include "Transform.h"

class GameEntity;

class MeshRenderer : public GameComponent
{
private:
	
	Material* _material;
	Mesh* _mesh;
	
public:
	
	
	/// <summary>Vertex buffer obj.</summary>
	unsigned int _vbo;
	/// <summary>Index buffer obj.</summary>
	unsigned int _ibo;
	MeshRenderer(GameEntity* gameEntity);
	MeshRenderer(GameEntity* gameEntity, Mesh* mesh, Material* material);
	~MeshRenderer();

	void Update() override;
	Mesh* GetMesh() const;
	Material* GetMaterial() const;
	void Init();
	void Bind(mat4 viewProjM, vec3 cameraWorldPos);
};