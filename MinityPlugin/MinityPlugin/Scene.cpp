#include "pch.h"
#include "Scene.h"
#include <iostream>
#include <fstream>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "../ObjectsLoaderAPIs/tiny_obj_loader.h"


vector<MeshRenderer*> LoadMeshRenderers(const string& objectPath);

vector<Mesh*> GetMeshes(const string& objectPath);

struct ShadersSource
{
	string vertexSource;
	string fragmentSource;
};

// Urgent refactor.
Scene::Scene()
{
	// I have to remove this later. An scene is able to exist without camera.
	_cameras.push_back(new Camera(glm::vec3(.0f, .0f, .0f), glm::vec2(-363, 220), 0));

	//auto meshRenderers = (LoadMeshRenderers("../OBJModels/worldtest2.obj"));
	auto meshRenderers = LoadMeshRenderers("OBJModels/Medieval/house.obj");
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
		};

		auto mesh = new Mesh(vertices, indices);

		Shader* shader = new Shader(sources.vertexSource, sources.fragmentSource);
		Material* material = new Material(shader);

		MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);
		renderers.push_back(meshRenderer);
	}
	else
	{
		vector<string> texturePath = 
		{ 
			"OBJModels/Medieval/ground_shadow.jpg",
			"OBJModels/Medieval/Ground_color.jpg",
			"OBJModels/Medieval/MillCat_color.jpg",
		};

		vector<Texture> textures;

		for (size_t i = 0; i < meshes.size(); i++)
		{
			Shader* shader = new Shader(sources.vertexSource, sources.fragmentSource);

			/*for (size_t i = 0; i < texturePath.size(); i++)
			{

			}*/

			Texture* texture = new Texture(texturePath[i]);

			Material* material = new Material(shader, texture);

			MeshRenderer* meshRenderer = new MeshRenderer(meshes[i], material);
			renderers.push_back(meshRenderer);
		}
	}

	return renderers;
}

vector<Mesh*> GetMeshes(const string& objectPath)
{
	vector<Mesh*> meshes;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

	bool load = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objectPath.c_str(), "OBJModels/", true);

	if (load)
	{
		for (size_t s = 0; s < shapes.size(); s++)
		{

			vector<float>* vertices = new vector<float>();
			vector<unsigned int>* indices = new vector<unsigned int>();

			size_t index_offset = 0;

			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) 
				{
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					vertices->push_back(attrib.vertices[3 * idx.vertex_index + 0]);
					vertices->push_back(attrib.vertices[3 * idx.vertex_index + 1]);
					vertices->push_back(attrib.vertices[3 * idx.vertex_index + 2]);

					vertices->push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
					vertices->push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);

					if (attrib.normals.size() > 3 * idx.normal_index + 2)
					{
						vertices->push_back(attrib.normals[3 * idx.normal_index + 0]);
						vertices->push_back(attrib.normals[3 * idx.normal_index + 1]);
						vertices->push_back(attrib.normals[3 * idx.normal_index + 2]);
					}
					else
					{
						vertices->push_back(0);
						vertices->push_back(0);
						vertices->push_back(0);
					}

					indices->push_back(index_offset + v);
				}

				index_offset += fv;
				
				// per-face material
				shapes[s].mesh.material_ids[f];
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