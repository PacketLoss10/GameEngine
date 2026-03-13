#include "BoxCollisionComponent.h"

BoxCollisionComponent::BoxCollisionComponent(Entity* owner) :CollisionComponent(owner) {}

const Vector2& BoxCollisionComponent::get_size() const
{
	return size;
}

void BoxCollisionComponent::set_size(const Vector2& size)
{
	this->size = size;
}