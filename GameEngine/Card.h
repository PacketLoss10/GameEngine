#pragma once

#include "Entity.h"
#include "BoxCollisionComponent.h"
#include "Sprite.h"

class Card :public Entity
{
private:
	Sprite* sprite;
	BoxCollisionComponent* collision;
public:
	Card();
	void cull() override {};
	void update_tick() override;
	void input_tick() override;
	void tap() {};

	void begin(Entity*, CollisionComponent*, const FVector&);
	void end(Entity*, CollisionComponent*, const FVector&);
};