#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "GameComponent.h"

class GameEntity;
using glm::vec4;
using glm::mat4;
using glm::vec3;

class Transform : public GameComponent
{
private:
	mat4 _model;
public:
	Transform(GameEntity* gameEntity);
	~Transform();

	void SetPosition(vec3 position);
	void SetRotation(vec3 position);
	void SetScale(vec3 scale);

	mat4 GetModelMatrix() const;
};

