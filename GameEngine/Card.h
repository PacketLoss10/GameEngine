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

	std::string id = "";

	bool tapped = false;
	bool flipped = false;
public:
	Card(std::string id);
	~Card();

	void cull() override {};
	void update_tick() override;
	void input_tick() override;

	void tap();
	void untap();

	void flip();
	void unflip();

	void mouse_hover(const Vector2&);
	void mouse_unhover(const Vector2&);
};