#include "Light.h"

void Light::init(Entity* owner, bool enabled, float radius, float brightness, Color color)
{
	this->owner = owner;
	this->enabled = enabled;
	this->radius = radius;
	this->brightness = brightness;
	this->color = color;
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