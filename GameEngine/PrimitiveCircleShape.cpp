#include "PrimitiveCircleShape.h"

PrimitiveCircleShape::PrimitiveCircleShape(FVector radius, Transform transform, Color fillColor, Color outlineColor) :PrimitiveShape(new sf::CircleShape, transform, fillColor, outlineColor), radius(radius) {}

const FVector& PrimitiveCircleShape::get_radius() const
{
	return radius;
}

void PrimitiveCircleShape::set_radius(const FVector& radius)
{
	this->radius = radius;
}