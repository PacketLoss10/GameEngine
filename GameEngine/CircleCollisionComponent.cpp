#include "CircleCollisionComponent.h"

CircleCollisionComponent::CircleCollisionComponent(Entity* owner) :CollisionComponent(owner) {}

const Vector2& CircleCollisionComponent::get_radius() const
{
	return radius;
}

void CircleCollisionComponent::set_radius(const Vector2& radius)
{
	this->radius = radius;
}