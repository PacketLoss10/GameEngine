#include "DragDropComponent.h"
#include "DragDropManager.h"

DragDropComponent::DragDropComponent(Entity* owner) :Component(owner) {}

void DragDropComponent::finalise()
{
	DRAG_DROP_MANAGER.register_component(this);
}

CollisionComponent* DragDropComponent::get_geometry() const
{
	return geometry;
}

void DragDropComponent::set_geometry(CollisionComponent* geometry)
{
	this->geometry = geometry;
}
