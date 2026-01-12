#include "BoxCollisionComponent.h"
#include "CollisionComponentManager.h"

BoxCollisionComponent::BoxCollisionComponent(FVector position, FVector size) :CollisionComponent(position), size(size) {}

void BoxCollisionComponent::init(Entity* owner, bool enabled, FVector position, FVector size)
{
	this->owner = owner;
	this->enabled = owner;
	this->position = position;
	this->size = size;
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