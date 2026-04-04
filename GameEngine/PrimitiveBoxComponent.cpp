#include "PrimitiveBoxComponent.h"

PrimitiveBoxComponent::PrimitiveBoxComponent(Entity* owner) :RenderComponent(owner), ZSortable(0) {}

RenderDataType PrimitiveBoxComponent::get_type() const
{
	return RenderDataType::Primitive;
}

PrimitiveRenderData PrimitiveBoxComponent::build_render_data() const
{
	PrimitiveRenderData data;

	data.type = PrimitiveType::Box;
	data.fillColor = fillColor;
	data.outlineColor = outlineColor;
	data.outlineThickness = outlineThickness;
	data.lighting = LightingData(lit, NormalMap());
	data.zOrder = get_zOrder();
	data.boxSize = size;
	data.transform = get_worldTransform();
	data.enabled = enabled;
	
	return data;
}

const Vector2& PrimitiveBoxComponent::get_size() const
{
	return size;
}

void PrimitiveBoxComponent::set_size(const Vector2& size)
{
	this->size = size;
}

const Color& PrimitiveBoxComponent::get_fillColor() const
{
	return fillColor;
}

void PrimitiveBoxComponent::set_fillColor(const Color& fillColor)
{
	this->fillColor = fillColor;
}

const Color& PrimitiveBoxComponent::get_outlineColor() const
{
	return outlineColor;
}

void PrimitiveBoxComponent::set_outlineColor(const Color& outlineColor)
{
	this->outlineColor = outlineColor;
}

float PrimitiveBoxComponent::get_outlineThickness() const
{
	return outlineThickness;
}

void PrimitiveBoxComponent::set_outlineThickness(float outlineThickness)
{
	this->outlineThickness = outlineThickness;
}

bool PrimitiveBoxComponent::is_lit() const
{
	return lit;
}

void PrimitiveBoxComponent::set_lit(bool lit)
{
	this->lit = lit;
}