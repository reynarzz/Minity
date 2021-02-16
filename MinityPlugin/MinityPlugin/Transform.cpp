#include "pch.h"

#include "GameComponent.h"
#include "GameEntity.h"
#include "Transform.h"

Transform::Transform(GameEntity* gameEntity) : GameComponent(gameEntity),
		  _position(1.f), _rotation(1.f), _scale(1.f)
{

}
mat4x4 Transform::GetModelMatrix() const 
{
	return _position * _rotation * _scale;
}

Transform::~Transform() 
{

}