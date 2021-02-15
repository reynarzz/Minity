#pragma once

#include <vector>
#include "MeshRenderer.h"
#include "MeshUtils.h"
#include "ShaderUtils.h"
#include "Scene.h"

class MeshSendToSceneTest
{
private:
	vector<MeshRenderer*> LoadMeshRenderers(const string& objectPath);
public:
	void SetMeshRenderersToScene(Scene* scene);
};

