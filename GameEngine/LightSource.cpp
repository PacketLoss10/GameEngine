#include "LightSource.h"
#include "Renderer.h"

void LightSource::update()
{
}

float LightSource::get_radius() const
{
	return radius;
}

void LightSource::set_radius(float new_radius)
{
	radius = new_radius;
}

float LightSource::get_brightness() const
{
	return brightness;
}

void LightSource::set_brightness(float new_brightness)
{
	brightness = new_brightness;
}

Color LightSource::get_color() const
{
	return color;
}

void LightSource::set_color(Color new_color)
{
	color = new_color;
}