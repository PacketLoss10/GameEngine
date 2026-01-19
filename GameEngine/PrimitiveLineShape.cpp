#include "PrimitiveLineShape.h"

PrimitiveLineShape::PrimitiveLineShape(float length, float thickness, Transform transform, Color color) :PrimitiveShape(new sf::RectangleShape, transform, color, Color(0, 0, 0, 0)), length(length), thickness(thickness) {}

float PrimitiveLineShape::get_length() const
{
	return length;
}

void PrimitiveLineShape::set_length(float length)
{
	this->length = length;
}

float PrimitiveLineShape::get_thickness() const
{
	return thickness;
}

void PrimitiveLineShape::set_thickness(float thickness)
{
	this->thickness = thickness;
}