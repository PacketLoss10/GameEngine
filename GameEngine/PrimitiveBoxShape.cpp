#include "PrimitiveBoxShape.h"

PrimitiveBoxShape::PrimitiveBoxShape(FVector size, Transform transform, Color fillColor, Color outlineColor) :PrimitiveShape(new sf::RectangleShape, transform, fillColor, outlineColor), size(size) {}

const FVector& PrimitiveBoxShape::get_size() const
{
	return size;
}

void PrimitiveBoxShape::set_size(const FVector& size)
{
	this->size = size;
}