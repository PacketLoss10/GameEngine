#include "BoxCollisionComponent.h"
#include "CollisionComponentManager.h"

BoxCollisionComponent::BoxCollisionComponent(Entity* owner, bool enabled, Transform transform, FVector size) :CollisionComponent(owner, enabled, transform), size(size) {}

void BoxCollisionComponent::init()
{
	COLLISION_COMPONENT_MANAGER.register_component(this);
}

const FVector& BoxCollisionComponent::get_size() const
{
	return size;
}

void BoxCollisionComponent::set_size(const FVector& size)
{
	this->size = size;
}