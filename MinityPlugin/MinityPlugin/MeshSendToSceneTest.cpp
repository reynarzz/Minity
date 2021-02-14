#include "pch.h"
#include "MeshSendToSceneTest.h"

vector<MeshRenderer*> MeshSendToSceneTest::LoadMeshRenderers(const string& objectPath)
{
	auto sources = ParseShader("MinityRes/Shaders/TextureUnlit.shader");

	vector<Mesh*> meshes = LoadMeshes(objectPath);
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
		Shader* shader = new Shader(sources.vertexSource, sources.fragmentSource);

		Texture* texture = new Texture(texturePath[i]);

		Material* material = new Material(shader, texture);

		MeshRenderer* meshRenderer = new MeshRenderer(meshes[i], material);
		renderers.push_back(meshRenderer);
	}

	return renderers;
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