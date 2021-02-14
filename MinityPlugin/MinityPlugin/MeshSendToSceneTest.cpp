#include "pch.h"
#include "MeshSendToSceneTest.h"



Material::MatAttribs ConvertToMatAttribs(tinyobj::material_t mat);

vector<MeshRenderer*> MeshSendToSceneTest::LoadMeshRenderers(const string& objectPath)
{
	auto sources = ParseShader("MinityRes/Shaders/TextureUnlit.shader");

	vector<MeshData*> meshes = LoadMeshes(objectPath);
	vector<MeshRenderer*> renderers;

	vector<string> texturePath =
	{
		"MinityRes/Models/ground_shadow.jpg",
		"MinityRes/Models/Ground_color.jpg",
		"MinityRes/Models/MillCat_color.jpg",
	};

	vector<Texture> textures;

	for (size_t i = 0; i < meshes.size(); i++)
	{
		string name = meshes[i]->mat.name;

		Shader* shader = new Shader(sources.vertexSource, sources.fragmentSource);

		Texture* texture = new Texture(texturePath[i]);
		
		Material::MatAttribs attribs = ConvertToMatAttribs(meshes[i]->mat);
		
		Material* material = new Material(shader, attribs, texture);

		MeshRenderer* meshRenderer = new MeshRenderer(meshes[i]->mesh, material);
		renderers.push_back(meshRenderer);
	}

	return renderers;
}

Material::MatAttribs ConvertToMatAttribs(tinyobj::material_t mat)
{
	Material::MatAttribs attribs;
	attribs.ambient = mat.ambient;
	
	attribs.ior = mat.ior;

	return attribs;
}

// testing
void MeshSendToSceneTest::SetMeshRenderersToScene(Scene* scene)
{
	auto meshRenderers = LoadMeshRenderers("MinityRes/Models/House.obj");
	//auto meshRenderers = LoadMeshRenderers("MinityRes/Models/Marina_1276_OBJ.obj");
	
	for (auto renderer : meshRenderers)
	{
		scene->AddMeshRenderer(renderer);
	}
}