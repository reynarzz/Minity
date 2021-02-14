#include "pch.h"
#include "MeshUtils.h"
#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "../ObjectsLoaderAPIs/tiny_obj_loader.h"
#include "MeshRenderer.h"

vector<Mesh*> LoadMeshes(const string& objectPath)
{
	vector<Mesh*> meshes;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

	bool load = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objectPath.c_str(), "MinityRes/", true);

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

					// Set notmals
					if (attrib.normals.size() > 3 * idx.normal_index + 2)
					{
						vertices->push_back(attrib.normals[3 * idx.normal_index + 0]);
						vertices->push_back(attrib.normals[3 * idx.normal_index + 1]);
						vertices->push_back(attrib.normals[3 * idx.normal_index + 2]);
					}
					else
					{
						// if no normal data is found.
						vertices->push_back(1);
						vertices->push_back(1);
						vertices->push_back(1);
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

