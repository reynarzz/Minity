#pragma once
#include <vector>
#include <string>

#include "Mesh.h"


using std::vector;
using std::string;

vector<Mesh*> LoadMeshes(const string& objectPath);