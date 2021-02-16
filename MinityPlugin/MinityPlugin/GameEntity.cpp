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

template<class T>
T* GameEntity::GetComponent() 
{
	// slow
	for (auto component : _components)
	{
		if (static_cast<T>(component) != nullptr) 
		{
			return static_cast<T>(component);
		}
	}

	return nullptr;
}

void GameEntity::AddComponent(GameComponent* component)
{
	_components.push_back(component);
}

GameEntity::~GameEntity() 
{

}