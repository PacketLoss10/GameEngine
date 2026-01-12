#include "CircleCollisionComponent.h"
#include "CollisionComponentManager.h"

void CircleCollisionComponent::init(Entity* owner, bool enabled, FVector position, float radius)
{
	this->owner = owner;
	this->enabled = enabled;
	this->position = position;
	this->radius = radius;
	COLLISION_COMPONENT_MANAGER.register_component(this);
}

float CircleCollisionComponent::get_radius() const
{
	return radius;
}

void CircleCollisionComponent::set_radius(float radius)
{
	this->radius = radius;
}