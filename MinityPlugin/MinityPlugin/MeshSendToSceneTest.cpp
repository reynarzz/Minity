#include "pch.h"
#include "MeshSendToSceneTest.h"
#include "GameEntity.h"
#include <iostream>
#include <sstream>

MatAttribs ConvertToMatAttribs(tinyobj::material_t mat);

Shader* LoadShader(const string& path) 
{
	auto sources = ParseShader(path);
	return new Shader(sources.vertexSource, sources.fragmentSource);
}

vector<GameEntity*> MeshSendToSceneTest::LoadGameEntities(const string& objectPath)
{
	Shader* shader = LoadShader("MinityRes/Shaders/TextureLight.shader");

	vector<MeshData*> meshes = LoadMeshes(objectPath);
	vector<GameEntity*> gameEntities;

	/*vector<string> texturePath =
	{
		"MinityRes/Models/smooth.png",
	};*/
	
	/*vector<string> texturePath =
	{
		"MinityRes/Models/ground_shadow.jpg",
		"MinityRes/Models/Ground_color.jpg",
		"MinityRes/Models/MillCat_color.jpg",
	};*/

	vector<Texture> textures;

	int entityCount = 0;

	for (size_t i = 0; i < meshes.size(); i++)
	{
		string name = meshes[i]->mesh->GetName();


		//Texture* texture = new Texture(texturePath[i]);
		
		MatAttribs attribs = ConvertToMatAttribs(meshes[i]->mat);
		
		Material* material = new Material(shader, attribs/*, texture*/);

		std::stringstream ss;
		ss << entityCount;

		string fullName = name + ss.str();

		GameEntity* gameEntity = new GameEntity(fullName);

		gameEntity->AddComponent(new MeshRenderer(gameEntity, meshes[i]->mesh, material));

		gameEntities.push_back(gameEntity);
	}

	return gameEntities;
}

MatAttribs ConvertToMatAttribs(tinyobj::material_t mat)
{
	MatAttribs attribs;

	attribs.ambient = vec3(mat.ambient[0], mat.ambient[1], mat.ambient[2]);
	attribs.diffuse = vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
	attribs.dissolve = mat.dissolve;

	attribs.ior = mat.ior;

	return attribs;
}

// testing
void MeshSendToSceneTest::SetMeshRenderersToScene(Scene* scene)
{
	//auto gameEntities = LoadGameEntities("MinityRes/Models/cube.obj");
	//auto cube2 = LoadGameEntities("MinityRes/Models/cube.obj").at(0);

	auto gameEntities = LoadGameEntities("MinityRes/Models/CoffeeRestaurant.obj");
	auto groundGrid = LoadGameEntities("MinityRes/Models/GroundGrid.obj");

	//auto meshRenderers = LoadMeshRenderers("MinityRes/Models/Marina_1276_OBJ.obj");

	for (auto gameEntity : gameEntities)
	{
		scene->AddGameEntity(gameEntity);
	}

	//scene->AddGameEntity(cube2);

	//cube2->GetTransform()->SetPosition(vec3(-2, 2, 0));
	// Ground Grid
	auto renderer = groundGrid.at(0)->GetComponent<MeshRenderer>();
	auto material = renderer->GetMaterial();

	material->_blending.enabled = true;
	material->_blending._srcFactor = GL_SRC_ALPHA;
	material->_blending._dstFactor = GL_ONE_MINUS_SRC_ALPHA;


	material->GetMatAttribs().diffuse = vec3(0.2f, 0.2f, 0.2f);

	Shader* shader = LoadShader("MinityRes/Shaders/GroundGrid.shader");

	material->SetShader(shader);
	material->culling._enabled = false;

	//material->_renderMode = RenderMode::Lines;

	scene->AddGameEntity(groundGrid.at(0));
}