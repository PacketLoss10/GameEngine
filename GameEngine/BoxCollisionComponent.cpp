#include "BoxCollisionComponent.h"
#include "PrimitiveBoxShape.h"

BoxCollisionComponent::BoxCollisionComponent(Entity* owner) :CollisionComponent(owner) {}

const Vector2& BoxCollisionComponent::get_size() const
{
	return size;
}

void BoxCollisionComponent::set_size(const Vector2& size)
{
	this->size = size;
}

void BoxCollisionComponent::render(Window& window)
{
	PrimitiveBoxShape box = PrimitiveBoxShape(size, get_worldTransform(), Color(255, 0, 0, 30), Color(255, 0, 0, 255));
	window.display(*box, nullptr);
}
