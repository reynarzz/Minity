#pragma once
#include <vector>

#include "Entity.h"

using std::vector;
using std::string;

//class Entity;
class GameComponent;

class GameEntity : public Entity
{
private:
	vector<GameComponent*> _components;
public:

	GameEntity(string name);
	~GameEntity();

	void Update();

	template<typename T>
	T* GetComponent()
	{
		// slow
		for (auto component : _components)
		{
			if (dynamic_cast<T*>(component) != nullptr)
			{
				return dynamic_cast<T*>(component);
			}
		}

		return nullptr;
	}


	void RemoveComponent();
	bool ContainsComponent(GameComponent* component);

	void AddComponent(GameComponent* component);
};

