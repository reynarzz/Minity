#include "pch.h"
#include "GameComponent.h"
#include "Transform.h"

#include "GameEntity.h"

GameEntity::GameEntity(string name)
{
	_name = name;

	Transform* transform = new Transform(this);
	transform->_name = name;

	AddComponent(transform);
}

void GameEntity::Update() 
{
	for (auto component: _components)
	{
		component->Update();
	}
}

bool GameEntity::ContainsComponent(GameComponent* component)
{
	// TODO
	return false;
}

void GameEntity::RemoveComponent() 
{
	// TODO
}

void GameEntity::AddComponent(GameComponent* component)
{
	_components.push_back(component);
}

GameEntity::~GameEntity() 
{

}