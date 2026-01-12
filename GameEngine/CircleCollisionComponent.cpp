#include "CircleCollisionComponent.h"

CircleCollisionComponent::CircleCollisionComponent(FVector position, float radius) :CollisionComponent(position), radius(radius) {}

float CircleCollisionComponent::get_radius() const
{
	return radius;
}

void CircleCollisionComponent::set_radius(float radius)
{
	this->radius = radius;
}