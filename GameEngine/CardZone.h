#pragma once

#include "Entity.h"
#include "Card.h"
#include "SpriteComponent.h"
#include "BoxCollisionComponent.h"
#include "PrimitiveBoxComponent.h"
#include "TextComponent.h"
#include "DragDropComponent.h"
#include <deque>

class CardZone :public Entity
{
protected:
	SpriteComponent* sprite;
	BoxCollisionComponent* area;
	PrimitiveBoxComponent* outline;
	TextComponent* label;
	DragDropComponent* mouseInteraction;

	std::deque<Card*> cards;
public:
	CardZone();
	~CardZone();

	virtual void add_card(Card* card);
	virtual Card* remove_card();

	virtual void mouse_hover();
	virtual void mouse_unhover();
	virtual void drag_begin(const Vector2& mousePos);

	SpriteComponent* get_sprite() const;
	BoxCollisionComponent* get_area() const;
	PrimitiveBoxComponent* get_outline() const;
	TextComponent* get_label() const;
	DragDropComponent* get_mouseInteraction() const;
};