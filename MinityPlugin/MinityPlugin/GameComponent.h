#pragma once

#include "Entity.h"

class Transform;
class GameEntity;

class GameComponent : public Entity
{
private:
	GameEntity* _gameEntity;
	Transform* _transform;
public:
	GameComponent(GameEntity* parent);
	~GameComponent();
	bool _enabled = true;
	virtual void Update();

	GameEntity* GetGameEntity() const;
	Transform* GetTransform() const;
};

