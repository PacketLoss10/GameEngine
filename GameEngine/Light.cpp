#include "Light.h"

Light::Light(Entity* owner) :RenderComponent(owner) {}

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