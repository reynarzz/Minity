#include "pch.h"
#include "Scene.h"
#include <iostream>
#include <fstream>

#include <Obj/OBJ_Loader.h>
#include "MyOBJParser.h"

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "../Obj_load2/tiny_obj_loader.h"



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

	//tinyobj::attrib_t attrib;
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;
	//std::string warn;
	//std::string err;

	//bool load = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objectPath.c_str(), "OBJModels/", true);

	//
	//if (load) 
	//{
	//	for (size_t i = 0; i < shapes.size(); i++)
	//	{
	//		vector<float>* vertices = new vector<float>();
	//		vector<unsigned int>* indices = new vector<unsigned int>();

	//		size_t v = 0;
	//		size_t t = 0;
	//		size_t n = 0;

	//		int vIndex = 0;

	//		for (; v < attrib.vertices.size() / 3; v++)
	//		{
	//			int vCount = 0;
	//			int tCount = 0;
	//			int nCount = 0;

	//			for (; v < attrib.vertices.size() / 3; v++)
	//			{
	//				vCount++;

	//				vertices->push_back(attrib.vertices[3 * v + 0]);
	//				vertices->push_back(attrib.vertices[3 * v + 1]);
	//				vertices->push_back(attrib.vertices[3 * v + 2]);

	//				/*static_cast<const double>(attrib.vertices[3 * v + 0]);
	//				static_cast<const double>(attrib.vertices[3 * v + 1]);
	//				static_cast<const double>(attrib.vertices[3 * v + 2]);*/

	//				if (vCount == 3)
	//				{
	//					break;
	//				}
	//			}

	//			for (; t < attrib.texcoords.size() / 2; t++)
	//			{
	//				tCount++;

	//				vertices->push_back(attrib.texcoords[2 * t + 0]);
	//				vertices->push_back(attrib.texcoords[2 * t + 1]);

	//				/*static_cast<const double>(attrib.texcoords[2 * t + 0]);
	//				static_cast<const double>(attrib.texcoords[2 * t + 1]);*/

	//				if (tCount == 2)
	//				{
	//					break;
	//				}
	//			}

	//			for (; n < attrib.normals.size() / 3; n++)
	//			{
	//				nCount++;

	//				vertices->push_back(attrib.normals[3 * n + 0]);
	//				vertices->push_back(attrib.normals[3 * n + 1]);
	//				vertices->push_back(attrib.normals[3 * n + 2]);

	//				/*static_cast<const double>(attrib.normals[3 * n + 0]);
	//				static_cast<const double>(attrib.normals[3 * n + 1]);
	//				static_cast<const double>(attrib.normals[3 * n + 2]);*/

	//				if (nCount == 3)
	//				{
	//					break;
	//				}
	//			}
	//		}


	//		for (size_t j = 0; j < shapes[i].mesh.indices.size(); j++)
	//		{
	//			indices->push_back((unsigned int)shapes[i].mesh.indices[j].vertex_index);
	//		}

	//		meshes.push_back(new Mesh(vertices, indices));
	//	}
	//}
	


	Loader loader;
	bool loaded = loader.LoadFile(objectPath);

	if (loaded)
	{
		for (int i = 0; i < loader.LoadedMeshes.size(); i++)
		{
			objl::Mesh mesh = loader.LoadedMeshes[i];

			vector<float>* vertices = new vector<float>();
			vector<unsigned int>* indices = new vector<unsigned int>();
			Debug::Log((unsigned int)loader.LoadedMeshes.size());

			for (int j = 0; j < mesh.Vertices.size(); j++)
			{
				auto vertex = mesh.Vertices[j];

				vertices->push_back(-vertex.Position.X);
				vertices->push_back(vertex.Position.Y);
				vertices->push_back(-vertex.Position.Z);

				vertices->push_back(vertex.TextureCoordinate.X);
				vertices->push_back(vertex.TextureCoordinate.Y);

				vertices->push_back(vertex.Normal.X);
				vertices->push_back(vertex.Normal.Y);
				vertices->push_back(vertex.Normal.Z);
			}

			for (int j = 0; j < mesh.Indices.size(); j++)
			{
				indices->push_back(mesh.Indices[j]);
			}

			meshes.push_back(new Mesh(vertices, indices));
		}
	}

	return meshes;
}

//void Example(const char* filePath)
//{
//	tinyobj::attrib_t attrib;
//	std::vector<tinyobj::shape_t> shapes;
//	std::vector<tinyobj::material_t> materials;
//	std::string warn;
//	std::string err;
//
//	tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath);
//
//	for (size_t v = 0; v < attrib.vertices.size() / 3; v++)
//	{
//		//printf("  v[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
//		static_cast<const double>(attrib.vertices[3 * v + 0]);
//		static_cast<const double>(attrib.vertices[3 * v + 1]);
//		static_cast<const double>(attrib.vertices[3 * v + 2]);
//	}
//
//	for (size_t v = 0; v < attrib.normals.size() / 3; v++)
//	{
//		//printf("  n[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
//		static_cast<const double>(attrib.normals[3 * v + 0]);
//		static_cast<const double>(attrib.normals[3 * v + 1]);
//		static_cast<const double>(attrib.normals[3 * v + 2]);
//	}
//
//	for (size_t v = 0; v < attrib.texcoords.size() / 2; v++)
//	{
//		//printf("  uv[%ld] = (%f, %f)\n", static_cast<long>(v),
//		static_cast<const double>(attrib.texcoords[2 * v + 0]);
//		static_cast<const double>(attrib.texcoords[2 * v + 1]);
//	}
//
//	for (size_t i = 0; i < shapes.size(); i++)
//	{
//		printf("shape[%ld].name = %s\n", static_cast<long>(i),
//			shapes[i].name.c_str());
//		printf("Size of shape[%ld].mesh.indices: %lu\n", static_cast<long>(i),
//			static_cast<unsigned long>(shapes[i].mesh.indices.size()));
//		printf("Size of shape[%ld].lines.indices: %lu\n", static_cast<long>(i),
//			static_cast<unsigned long>(shapes[i].lines.indices.size()));
//		printf("Size of shape[%ld].points.indices: %lu\n", static_cast<long>(i),
//			static_cast<unsigned long>(shapes[i].points.indices.size()));
//
//		size_t index_offset = 0;
//
//		/*assert(shapes[i].mesh.num_face_vertices.size() ==
//			shapes[i].mesh.material_ids.size());
//
//		assert(shapes[i].mesh.num_face_vertices.size() ==
//			shapes[i].mesh.smoothing_group_ids.size());*/
//
//			/*	printf("shape[%ld].num_faces: %lu\n", static_cast<long>(i),
//					static_cast<unsigned long>(shapes[i].mesh.num_face_vertices.size()));*/
//
//					// For each face
//		for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++)
//		{
//			size_t fnum = shapes[i].mesh.num_face_vertices[f];
//
//			/*printf("  face[%ld].fnum = %ld\n", static_cast<long>(f),
//				static_cast<unsigned long>(fnum));*/
//
//				// For each vertex in the face
//			for (size_t v = 0; v < fnum; v++)
//			{
//				tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + v];
//				/*printf("    face[%ld].v[%ld].idx = %d/%d/%d\n", static_cast<long>(f),
//					static_cast<long>(v), idx.vertex_index, idx.normal_index,
//					idx.texcoord_index);*/
//			}
//
//			/*printf("  face[%ld].material_id = %d\n", static_cast<long>(f),
//				shapes[i].mesh.material_ids[f]);
//			printf("  face[%ld].smoothing_group_id = %d\n", static_cast<long>(f),
//				shapes[i].mesh.smoothing_group_ids[f]);*/
//
//			index_offset += fnum;
//		}
//
//		/*printf("shape[%ld].num_tags: %lu\n", static_cast<long>(i),
//			static_cast<unsigned long>(shapes[i].mesh.tags.size()));*/
//		for (size_t t = 0; t < shapes[i].mesh.tags.size(); t++)
//		{
//			/*printf("  tag[%ld] = %s ", static_cast<long>(t),
//				shapes[i].mesh.tags[t].name.c_str());
//			printf(" ints: [");*/
//			for (size_t j = 0; j < shapes[i].mesh.tags[t].intValues.size(); ++j)
//			{
//				/*printf("%ld", static_cast<long>(shapes[i].mesh.tags[t].intValues[j]));*/
//				if (j < (shapes[i].mesh.tags[t].intValues.size() - 1))
//				{
//					printf(", ");
//				}
//			}
//			//printf("]");
//
//			//printf(" floats: [");
//			for (size_t j = 0; j < shapes[i].mesh.tags[t].floatValues.size(); ++j)
//			{
//				/*printf("%f", static_cast<const double>(
//					shapes[i].mesh.tags[t].floatValues[j]));*/
//				if (j < (shapes[i].mesh.tags[t].floatValues.size() - 1))
//				{
//					//printf(", ");
//				}
//			}
//			//printf("]");
//
//			//printf(" strings: [");
//			for (size_t j = 0; j < shapes[i].mesh.tags[t].stringValues.size(); ++j)
//			{
//				//printf("%s", shapes[i].mesh.tags[t].stringValues[j].c_str());
//				if (j < (shapes[i].mesh.tags[t].stringValues.size() - 1))
//				{
//					//printf(", ");
//				}
//			}
//			//printf("]");
//			//printf("\n");
//		}
//	}
//}

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