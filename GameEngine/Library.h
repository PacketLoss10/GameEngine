#pragma once

#include "Entity.h"
#include "queue"

class Card;
class SpriteComponent;
class BoxCollisionComponent;
class PrimitiveBoxComponent;
class TextComponent;
class DragDropComponent;

class Library :public Entity
{
private:
	SpriteComponent* sprite;
	BoxCollisionComponent* collision;
	PrimitiveBoxComponent* outline;
	TextComponent* label;
	DragDropComponent* dragDrop;

	std::deque<Card*> cards;
public:
	Library();
	~Library();

	Card* draw_card();
	void place_card(Card* card);

	void mouse_hover();
	void mouse_unhover();
	void drag_begin(const Vector2&);

	SpriteComponent* get_sprite() const;
	BoxCollisionComponent* get_collision() const;
	PrimitiveBoxComponent* get_outline() const;
	TextComponent* get_label() const;
	DragDropComponent* get_dragDrop() const;
};