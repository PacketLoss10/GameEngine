#pragma once

#include "Entity.h"
#include "SpriteComponent.h"
#include "BoxCollisionComponent.h"
#include "Card.h"
#include <queue>

enum class LibraryPosition
{
	Top, Bottom
};

class Library :public Entity
{
private:
	SpriteComponent* sprite;
	BoxCollisionComponent* collision;
	std::deque<Card*> library;
public:
	Library();
	~Library();

	Card* draw_card();
	void add_card(Card* card, LibraryPosition at);
	void shuffle();

	BoxCollisionComponent* get_collision() const { return collision; }
};