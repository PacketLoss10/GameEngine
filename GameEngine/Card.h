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

	void mouse_overlap_begin(Entity*, CollisionComponent*, const Vector2&);
	void mouse_overlap_end(Entity*, CollisionComponent*, const Vector2&);

	void overlap_begin(Entity*, CollisionComponent*, Entity*, CollisionComponent*);
	void overlap_end(Entity*, CollisionComponent*, Entity*, CollisionComponent*);
};