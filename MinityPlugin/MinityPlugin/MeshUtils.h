#pragma once
#include <vector>
#include <string>

#include "Mesh.h"
#include "../ObjectsLoaderAPIs/tiny_obj_loader.h"


using std::vector;
using std::string;



class MeshData
{
public:
	Mesh* mesh;
	tinyobj::material_t mat;
};


vector<MeshData*> LoadMeshes(const string& objectPath);