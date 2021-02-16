#include "pch.h"

#include "GameComponent.h"

GameComponent::GameComponent(GameEntity* gameEntity) : _gameEntity(gameEntity)
{

}

void GameComponent::Update() 
{
}

GameEntity* GameComponent::GetGameEntity() const 
{
	return _gameEntity;
}

GameComponent::~GameComponent() 
{

}