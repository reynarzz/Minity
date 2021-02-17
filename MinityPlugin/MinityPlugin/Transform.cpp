#include "pch.h"

#include <glm/ext/matrix_transform.hpp>

#include "Transform.h"

Transform::Transform(GameEntity* gameEntity) : GameComponent(gameEntity),
					 _model(1.f)
		  
{
	
}

mat4 Transform::GetModelMatrix() const 
{
	return _model;
}

void Transform::SetPosition(vec3 position) 
{
	_model = glm::translate(_model, position);
}

void Transform::SetRotation(vec3 rotation) 
{
	if (rotation.y != 0)
	{
		_model = glm::rotate(_model, glm::radians(rotation.y), vec3(0, 1.f, 0));
	}

	if (rotation.x != 0) 
	{
		_model = glm::rotate(_model, glm::radians(rotation.x), vec3(1.f, 0, 0));
	}

	if (rotation.z != 0)
	{
		_model = glm::rotate(_model, glm::radians(rotation.z), vec3(0, 0, 1.f));
	}
}
 

void Transform::SetScale(vec3 scale) 
{
	_model = glm::scale(_model, scale);
}

Transform::~Transform()
{

}