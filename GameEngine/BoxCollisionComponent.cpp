#include "BoxCollisionComponent.h"

BoxCollisionComponent::BoxCollisionComponent(FVector position, FVector size) :CollisionComponent(position), size(size) {}

const FVector& BoxCollisionComponent::get_size() const
{
	return size;
}

void BoxCollisionComponent::set_size(const FVector& size)
{
	this->size = size;
}