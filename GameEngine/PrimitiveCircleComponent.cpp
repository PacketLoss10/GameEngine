#include "PrimitiveCircleComponent.h"

PrimitiveCircleComponent::PrimitiveCircleComponent(Entity* owner) :RenderComponent(owner), ZSortable(0) {}

RenderDataType PrimitiveCircleComponent::get_type() const
{
	return RenderDataType::Primitive;
}

PrimitiveRenderData PrimitiveCircleComponent::build_render_data() const
{
	PrimitiveRenderData data;

	data.type = PrimitiveType::Circle;
	data.fillColor = fillColor;
	data.outlineColor = outlineColor;
	data.outlineThickness = outlineThickness;
	data.lighting = LightingData(lit, NormalMap());
	data.zOrder = get_zOrder();
	data.circleRadius = radius;
	data.transform = get_worldTransform();
	data.enabled = enabled;

	return data;
}

const Vector2& PrimitiveCircleComponent::get_radius() const
{
	return radius;
}

void PrimitiveCircleComponent::set_radius(const Vector2& radius)
{
	this->radius = radius;
}

const Color& PrimitiveCircleComponent::get_fillColor() const
{
	return fillColor;
}

void PrimitiveCircleComponent::set_fillColor(const Color& fillColor)
{
	this->fillColor = fillColor;
}

const Color& PrimitiveCircleComponent::get_outlineColor() const
{
	return outlineColor;
}

void PrimitiveCircleComponent::set_outlineColor(const Color& outlineColor)
{
	this->outlineColor = outlineColor;
}

float PrimitiveCircleComponent::get_outlineThickness() const
{
	return outlineThickness;
}

void PrimitiveCircleComponent::set_outlineThickness(float outlineThickness)
{
	this->outlineThickness = outlineThickness;
}

bool PrimitiveCircleComponent::is_lit() const
{
	return lit;
}

void PrimitiveCircleComponent::set_lit(bool lit)
{
	this->lit = lit;
}
