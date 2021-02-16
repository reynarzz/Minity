#pragma once
#include <glm/glm.hpp>

class GameComponent;
class GameEntity;

using glm::vec4;
using glm::mat4x4;

class Transform : public GameComponent
{
private:
public:
	Transform(GameEntity* gameEntity);
	~Transform();
	mat4x4 _position;
	mat4x4 _scale;
	mat4x4 _rotation;

	mat4x4 GetModelMatrix() const;
};

