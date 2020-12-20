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
	_cameras.push_back(new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, -90.0f), 0));

	//auto meshRenderers = (LoadMeshRenderers("../OBJModels/worldtest2.obj"));
	auto meshRenderers = LoadMeshRenderers("../OBJModels/DemoScene.obj");
	//auto meshRenderers = LoadMeshRenderers("../OBJModels/Character.obj");

	for (auto renderer : meshRenderers)
	{
		_objects.push_back(renderer);
	}
}

static ShadersSource ParseShader(const string shaderFilePath)
{
	std::ifstream stream(shaderFilePath);

	enum ShaderType
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
	auto sources = ParseShader("DepthShader.shader");

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
			Material* material = new Material(shader);

			MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);
			renderers.push_back(meshRenderer);
		}

	}
	
	return renderers;
}

vector<Mesh*> GetMeshes(const string& objectPath)
{
	Mesh* mesh = nullptr;
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
			objl::Mesh curMesh = loader.LoadedMeshes[i];

			vector<float>* vertices = new vector<float>();
			vector<unsigned int>* indices = new vector<unsigned int>();

			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{
				vertices->push_back(-curMesh.Vertices[j].Position.X * 0.5f);
				vertices->push_back(curMesh.Vertices[j].Position.Y * 0.5f);
				vertices->push_back(-curMesh.Vertices[j].Position.Z * 0.5f);

				/*"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
				"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
				"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";*/
			}

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				indices->push_back(curMesh.Indices[j]);
				indices->push_back(curMesh.Indices[j + 1]);
				indices->push_back(curMesh.Indices[j + 2]);
				//file << "T" << j / 3 << ": " <<  << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
			}

			mesh = new Mesh(vertices, indices);

			meshes.push_back(mesh);
		}
		
	}

	/*auto obj = ParseOBJModel("../OBJModels/boat.obj");

	for (auto vert : obj.verts)
	{
		vertices->push_back(vert.x * 0.2f);
		vertices->push_back(vert.y * 0.2f);
		vertices->push_back(-vert.z * 0.2f);
	}

	for (auto indice : obj.elements)
	{
		indices->push_back(indice);
	}

	mesh = new Mesh(vertices, indices);*/

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

void Scene::SetAspectRatio(float aspect)
{
	for (auto camera : _cameras)
	{
		camera->UpdateProjectionMatrix(aspect);
	}
}

Scene::~Scene()
{
	// Clear destroys the objects!
	_objects.clear();
	_objects.shrink_to_fit();
}