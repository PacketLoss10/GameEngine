#include "LightComponent.h"

LightComponent::LightComponent(Entity* owner) :RenderComponent(owner) {}

RenderDataType LightComponent::get_type() const
{
	return RenderDataType::Light;
}

LightRenderData LightComponent::build_render_data() const
{
	LightRenderData data;

	data.radius = radius;
	data.brightness = brightness;
	data.color = color;
	data.position = get_worldPosition();
	data.enabled = enabled;

	return data;
}

float LightComponent::get_radius() const
{
	return radius;
}

void LightComponent::set_radius(float radius)
{
	this->radius = radius;
}

float LightComponent::get_brightness() const
{
	return brightness;
}

void LightComponent::set_brightness(float brightness)
{
	this->brightness = brightness;
}

const Color& LightComponent::get_color() const
{
	return color;
}

void LightComponent::set_color(const Color& color)
{
	this->color = color;
}