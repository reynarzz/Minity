#include "pch.h"
#include "GameEntity.h"
#include "Transform.h"
#include "GameComponent.h"

GameComponent::GameComponent(GameEntity* parent) : 
	_gameEntity(parent)/*, 
	_transform(_gameEntity->GetTransform())*/
{

}

void GameComponent::Update() 
{
}

GameEntity* GameComponent::GetGameEntity() const
{
	return _gameEntity;
}

Transform* GameComponent::GetTransform() const 
{
	return _gameEntity->GetTransform();
}

GameComponent::~GameComponent() 
{

}