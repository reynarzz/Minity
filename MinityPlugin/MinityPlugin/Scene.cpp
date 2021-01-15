#include "pch.h"
#include "Scene.h"
#include <iostream>
#include <fstream>

#include <Obj/OBJ_Loader.h>
#include "MyOBJParser.h"

vector<MeshRenderer*> LoadMeshRenderers(const string& objectPath);
using objl::Loader;

vector<Mesh*> GetMeshes(const string& objectPath);

struct ShadersSource
{
	string vertexSource;
	string fragmentSource;
};

Scene::Scene()
{
	// I have to remove this later. An scene is able to exist without camera.
	_cameras.push_back(new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec2(0.0f, -90.0f), 0));

	//auto meshRenderers = (LoadMeshRenderers("../OBJModels/worldtest2.obj"));
	auto meshRenderers = LoadMeshRenderers("OBJModels/Medieval/House.obj");
	//auto meshRenderers = LoadMeshRenderers("../OBJModels/Character.obj");

	for (auto renderer : meshRenderers)
	{
		_objects.push_back(renderer);
	}
}

static ShadersSource ParseShader(const string shaderFilePath)
{
	std::ifstream stream(shaderFilePath);

	enum class ShaderType
	{
		NONE = 2, VERTEX = 0, FRAGMENT = 1
	};


	string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	int sT = 0;

	while (std::getline(stream, line))
	{
		std::cout << line << std::endl;

		if (line.find("#shader") != string::npos)
		{
			if (line.find("VERTEX") != string::npos)
			{
				type = ShaderType::VERTEX;
				sT = 0;
			}
			else if (line.find("FRAGMENT") != string::npos)
			{
				type = ShaderType::FRAGMENT;
				sT = 1;
			}
		}
		else
		{
			ss[sT] << line << '\n';
		}

		//std::cout << "-: " << ss[sT].str() << std::endl;
	}

	return { ss[0].str(), ss[1].str() };
}

vector<MeshRenderer*> LoadMeshRenderers(const string& objectPath)
{
	auto sources = ParseShader("OBJModels/Shaders/Texture.shader");

	vector<Mesh*> meshes = GetMeshes(objectPath);
	vector<MeshRenderer*> renderers;

	if (meshes.size() == 0)
	{
		vector<float>* vertices = new vector<float>
		{
			0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, -1.0f,
			-1.0f, 0.0f, -1.0f,
		};

		vector<unsigned int>* indices = new vector<unsigned int>
		{
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 1
		};

		auto mesh = new Mesh(vertices, indices);

		Shader* shader = new Shader(sources.vertexSource, sources.fragmentSource);
		Material* material = new Material(shader);

		MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);
		renderers.push_back(meshRenderer);
	}
	else
	{
		for (auto mesh : meshes)
		{
			Shader* shader = new Shader(sources.vertexSource, sources.fragmentSource);
			//Texture* texture = new Texture("OBJModels/Medieval/MillCat_color.jpg");

			Material* material = new Material(shader);

			MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);
			renderers.push_back(meshRenderer);
		}
	}

	return renderers;
}

vector<Mesh*> GetMeshes(const string& objectPath)
{
	vector<Mesh*> meshes;

	Loader loader;
	bool loaded = loader.LoadFile(objectPath);

	if (loaded)
	{
		// Print Mesh Name
		// file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

		// Print Vertices
		// file << "Vertices:\n";

		// Go through each vertex and print its number,
		//  position, normal, and texture coordinate
		for (int i = 0; i < loader.LoadedMeshes.size(); i++)
		{
			objl::Mesh mesh = loader.LoadedMeshes[i];

			vector<float>* vertices = new vector<float>();
			vector<unsigned int>* indices = new vector<unsigned int>();

			for (int j = 0; j < mesh.Vertices.size(); j++)
			{
				vertices->push_back(-mesh.Vertices[j].Position.X);
				vertices->push_back(mesh.Vertices[j].Position.Y);
				vertices->push_back(-mesh.Vertices[j].Position.Z);

				vertices->push_back(mesh.Vertices[j].TextureCoordinate.X);
				vertices->push_back(mesh.Vertices[j].TextureCoordinate.Y);

				vertices->push_back(mesh.Vertices[j].Normal.X);
				vertices->push_back(mesh.Vertices[j].Normal.Y);
				vertices->push_back(mesh.Vertices[j].Normal.Z);
			}

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < mesh.Indices.size(); j += 3)
			{
				indices->push_back(mesh.Indices[j]);

				if (mesh.Indices.size() > j + 1)
				{
					indices->push_back(mesh.Indices[j + 1]);
				}

				if (mesh.Indices.size() > j + 2)
				indices->push_back(mesh.Indices[j + 2]);
			}

			meshes.push_back(new Mesh(vertices, indices));
		}

	}
	return meshes;
}

const vector<MeshRenderer*>& Scene::GetMeshRenderers() const
{
	return _objects;
}

const vector<Camera*>& Scene::GetCameras() const
{
	return _cameras;
}

void Scene::Update(ScreenInfo screenInfo, float deltaTime)
{
	for (auto camera : _cameras)
	{
		/*if (_screenInfo._dimensions.x != screenInfo._dimensions.x)
		{
			_screenInfo._dimensions.x = screenInfo._dimensions.x;

			camera->OnScreenSizeChanged(screenInfo._dimensions.x, screenInfo._dimensions.y);
			Debug::Log("Size changed");
		}*/

		camera->Update(deltaTime);
	}
}

Scene::~Scene()
{
	// Clear destroys the objects!
	_objects.clear();
	_objects.shrink_to_fit();
}