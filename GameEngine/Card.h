#pragma once

#include "Entity.h"
#include <string>

class SpriteComponent;
class BoxCollisionComponent;
class DragDropComponent;
class Library;
class CollisionComponent;

class Card :public Entity
{
private:
	SpriteComponent* sprite;
	BoxCollisionComponent* collision;
	DragDropComponent* dragDrop;

	Library* overlappingLibrary = nullptr;

	std::string id = "";

	bool tapped = false;
	bool flipped = false;
	bool zoomed = false;
public:
	Card(std::string id);
	~Card();

	void update_tick() override;
	void input_tick() override;

	void tap();
	void untap();

	void flip();
	void unflip();

	void mouse_hover();
	void mouse_unhover();

	void overlap_begin(CollisionComponent* collision, Entity* otherEntity, CollisionComponent* otherCollision);
	void overlap_end(CollisionComponent* collision, Entity* otherEntity, CollisionComponent* otherCollision);

	void drag_end(const Vector2&);

	SpriteComponent* get_sprite() const;
	BoxCollisionComponent* get_collision() const;
	DragDropComponent* get_dragDrop() const;
};