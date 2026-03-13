#include "PrimitiveCircleShape.h"

PrimitiveCircleShape::PrimitiveCircleShape(Vector2 radius, Transform transform, Color fillColor, Color outlineColor) :PrimitiveShape(new sf::CircleShape, transform, fillColor, outlineColor), radius(radius) {}

const Vector2& PrimitiveCircleShape::get_radius() const
{
	return radius;
}

void PrimitiveCircleShape::set_radius(const Vector2& radius)
{
	this->radius = radius;
}