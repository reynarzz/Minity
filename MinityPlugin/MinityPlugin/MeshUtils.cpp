#include "pch.h"
#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "MeshUtils.h"
#include "MeshRenderer.h"


vector<MeshData*> LoadMeshes(const string& objectPath)
{
	vector<MeshData*> meshes;

	
	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "MinityRes/Models/"; // Path to material files

	tinyobj::ObjReader reader;

	bool load = reader.ParseFromFile(objectPath, reader_config);

	//if (!reader.ParseFromFile(inputfile, reader_config)) {
	//	if (!reader.Error().empty()) {
	//		//std::cerr << "TinyObjReader: " << reader.Error();
	//	}
	//	//exit(1);
	//}

	//if (!reader.Warning().empty()) {
	//	//std::cout << "TinyObjReader: " << reader.Warning();
	//}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();


	if (load)
	{
		for (size_t s = 0; s < shapes.size(); s++)
		{
			vector<float>* vertices = new vector<float>();
			vector<unsigned int>* indices = new vector<unsigned int>();

			size_t index_offset = 0;

			int testMat = 0;
			// Face
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

				// per-face material -- (but for now using it for the entire mesh)
				testMat = shapes[s].mesh.material_ids[f];
			}

			Mesh* mesh = new Mesh(vertices, indices);
			mesh->SetName(shapes[s].name);

			MeshData* data = new MeshData();
			data->mesh = mesh;

			if(materials.size() > 0)
			data->mat = materials[testMat];
			else 
			{
				tinyobj::material_t defaultMat;
				
				defaultMat.ambient[0] = 1;
				defaultMat.ambient[1] = 1;
				defaultMat.ambient[2] = 1;

				data->mat = defaultMat;

			}
			meshes.push_back(data);
		}
	}

	return meshes;
}

