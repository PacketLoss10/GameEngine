#pragma once

#include "Entity.h"
#include "BoxCollisionComponent.h"
#include "DragDropComponent.h"
#include "Sprite.h"

class Card :public Entity
{
private:
	Sprite* sprite;
	BoxCollisionComponent* collision;
	DragDropComponent* dragDrop;

	bool tapped = false;
public:
	Card();
	~Card();

	void cull() override {};
	void update_tick() override;
	void input_tick() override;

	void tap();
	void untap();

	void bring_to_front(const Vector2&);
};