#include "PrimitiveShape.h"

PrimitiveShape::PrimitiveShape(sf::Drawable* shape, Transform transform, Color fillColor, Color outlineColor) :Transformable(transform), shape(shape), fillColor(fillColor), outlineColor(outlineColor) {}

PrimitiveShape::~PrimitiveShape()
{
	delete shape;
}

const Color& PrimitiveShape::get_fillColor() const
{
	return fillColor;
}

void PrimitiveShape::set_fillColor(const Color& fillColor)
{
	this->fillColor = fillColor;
}

const Color& PrimitiveShape::get_outlineColor() const
{
	return outlineColor;
}

void PrimitiveShape::set_outlineColor(const Color& outlineColor)
{
	this->outlineColor = outlineColor;
}