#include "CircleCollisionComponent.h"
#include "CollisionComponentManager.h"

CircleCollisionComponent::CircleCollisionComponent(Entity* owner, bool enabled, Transform transform, FVector radius) :CollisionComponent(owner, enabled, transform), radius(radius) {}

void CircleCollisionComponent::init()
{
	COLLISION_COMPONENT_MANAGER.register_component(this);
}

const FVector& CircleCollisionComponent::get_radius() const
{
	return radius;
}

void CircleCollisionComponent::set_radius(const FVector& radius)
{
	this->radius = radius;
}