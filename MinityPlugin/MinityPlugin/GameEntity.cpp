#include "pch.h"
#include "GameComponent.h"
#include "Transform.h"

#include "GameEntity.h"

GameEntity::GameEntity(string name)
{
	_name = name;

	_transform = new Transform(this);
	_transform->_name = name;
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

Transform* GameEntity::GetTransform() const 
{
	return _transform;
}

GameEntity::~GameEntity() 
{
	_components.clear();

	delete _transform;
}