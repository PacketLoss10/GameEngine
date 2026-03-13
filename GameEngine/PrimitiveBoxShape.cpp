#include "PrimitiveBoxShape.h"

PrimitiveBoxShape::PrimitiveBoxShape(Vector2 size, Transform transform, Color fillColor, Color outlineColor) :PrimitiveShape(new sf::RectangleShape, transform, fillColor, outlineColor), size(size) {}

const Vector2& PrimitiveBoxShape::get_size() const
{
	return size;
}

void PrimitiveBoxShape::set_size(const Vector2& size)
{
	this->size = size;
}