#include "CollisionComponent.h"
#include "CollisionComponentManager.h"

bool CollisionComponent::is_overlapping(CollisionComponent* overlap) const
{
	return overlaps.contains(overlap);
}

void CollisionComponent::add_overlap(CollisionComponent* overlap)
{
	overlaps.insert(overlap);
}

void CollisionComponent::remove_overlap(CollisionComponent* overlap)
{
	overlaps.erase(overlap);
}

bool CollisionComponent::is_mouseOverlapping() const
{
	return mouseOverlapping;
}

void CollisionComponent::set_mouseOverlapping(bool mouseOverlapping)
{
	this->mouseOverlapping = mouseOverlapping;
}

void CollisionComponent::finalise()
{
	COLLISION_COMPONENT_MANAGER.register_component(this);
}

CollisionComponent::CollisionComponent(Entity* owner) :Component(owner) {}