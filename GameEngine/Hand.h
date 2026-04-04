#pragma once

#include "Entity.h"
#include "BoxCollisionComponent.h"
#include "PrimitiveBoxComponent.h"
#include "TextComponent.h"

class Hand :public Entity
{
private:
	BoxCollisionComponent* area;
	PrimitiveBoxComponent* outline;
	TextComponent* label;
public:
	Hand();
	~Hand();

	void mouse_hover();
	void mouse_unhover();
	void drag_begin(const Vector2& mousePos);

	BoxCollisionComponent* get_area() const;
	PrimitiveBoxComponent* get_outline() const;
	TextComponent* get_label() const;
};