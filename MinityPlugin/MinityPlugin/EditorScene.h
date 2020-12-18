#pragma once
#include "Camera.h"

class EditorScene
{
private:
	Camera* _camera;

	glm::vec3 _pos = glm::vec3(0.0f, 0.0f, -3.0f);
	glm::vec3 _rot;
	glm::vec2 _mousePos;
	glm::vec2 _mouseDelta;
public:
	EditorScene(Camera* camera);
	~EditorScene();

	//mat4 model = glm::mat4(1.0f);

	//model = glm::translate(model, _pos);
	//model = glm::rotate(model, _time /* 3.14f / 180*/, glm::vec3(0.0f, 1.0f, 0.0f));

};

