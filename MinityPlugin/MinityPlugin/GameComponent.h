#pragma once

#include "Entity.h"

class GameEntity;

class GameComponent : public Entity
{
private:
	GameEntity* _gameEntity;
public:
	GameComponent(GameEntity* parent);
	~GameComponent();
	bool _enabled = true;
	virtual void Update();

	GameEntity* GetGameEntity() const;
};

