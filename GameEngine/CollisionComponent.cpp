#include "CollisionComponent.h"
#include "CollisionComponentManager.h"

CollisionComponent::CollisionComponent(FVector position):position(position)
{
	CollisionComponentManager::instance().register_component(this);
}

const FVector& CollisionComponent::get_position() const
{
	return position;
}

void CollisionComponent::set_position(const FVector& position)
{
	this->position = position;
}