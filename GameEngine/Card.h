#pragma once

#include "Entity.h"
#include "SpriteComponent.h"
#include "BoxCollisionComponent.h"
#include "DragDropComponent.h"
#include <string>

class CardZone;

class Card :public Entity
{
private:
	SpriteComponent* sprite;
	BoxCollisionComponent* collision;
	DragDropComponent* dragDrop;

	std::string front = "";
	std::string back = "";

	bool tapped = false;
	bool flipped = false;
	bool zoomed = false;
public:
	Card(std::string front, std::string back);
	~Card();

	void update_tick() override;
	void input_tick() override;

	void tap();
	void untap();

	void flip();
	void unflip();

	void zoom();
	void unzoom();

	void mouse_hover();
	void mouse_unhover();

	void drag_end(const Vector2& mousePos);

	SpriteComponent* get_sprite() const;
	BoxCollisionComponent* get_collision() const;
	DragDropComponent* get_dragDrop() const;
};