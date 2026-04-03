#include "DragDropComponent.h"
#include "DragDropManager.h"

DragDropComponent::DragDropComponent(Entity* owner) :Component(owner) {}

void DragDropComponent::spawn()
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

int DragDropComponent::get_layer() const
{
	return layer;
}

void DragDropComponent::set_layer(int layer)
{
	this->layer = layer;
}

const Vector2& DragDropComponent::get_dragStartMousePos() const
{
	return dragStartMousePos;
}

void DragDropComponent::set_dragStartMousePos(const Vector2& dragStartMousePos)
{
	this->dragStartMousePos = dragStartMousePos;
}

const Vector2& DragDropComponent::get_dragStartEntityPos() const
{
	return dragStartEntityPos;
}

void DragDropComponent::set_dragStartEntityPos(const Vector2& dragStartEntityPos)
{
	this->dragStartEntityPos = dragStartEntityPos;
}

const Vector2& DragDropComponent::get_dragOffset() const
{
	return dragOffset;
}

void DragDropComponent::set_dragOffset(const Vector2& dragOffset)
{
	this->dragOffset = dragOffset;
}