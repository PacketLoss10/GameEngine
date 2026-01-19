#include "Light.h"
#include "RenderComponentManager.h"

Light::Light(Entity* owner, bool enabled, Transform transform, float radius, float brightness, Color color) :RenderComponent(owner, enabled, transform), radius(radius), brightness(brightness), color(color) {}

void Light::init()
{
	RENDER_COMPONENT_MANAGER.register_component(this);
}

float Light::get_radius() const
{
	return radius;
}

void Light::set_radius(float radius)
{
	this->radius = radius;
}

float Light::get_brightness() const
{
	return brightness;
}

void Light::set_brightness(float brightness)
{
	this->brightness = brightness;
}

const Color& Light::get_color() const
{
	return color;
}

void Light::set_color(const Color& color)
{
	this->color = color;
}