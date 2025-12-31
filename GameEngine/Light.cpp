#include "Light.h"
#include "Renderer.h"

Light::Light(float radius, float brightness, Color color) 
	:Renderable(Transform()),
	radius(radius), 
	brightness(brightness),
	color(color)
{
}

float Light::get_radius() const
{
	return radius;
}

void Light::set_radius(float new_radius)
{
	radius = new_radius;
}

float Light::get_brightness() const
{
	return brightness;
}

void Light::set_brightness(float new_brightness)
{
	brightness = new_brightness;
}

Color Light::get_color() const
{
	return color;
}

void Light::set_color(Color new_color)
{
	color = new_color;
}