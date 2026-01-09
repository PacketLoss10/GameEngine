#pragma once

#include "core.h"
#include "RenderObject.h"

class Light :public RenderObject
{
private:
	float radius;
	float brightness;
	Color color;
public:
	Light(float radius, float brightness, Color color);
	float get_radius() const;
	void set_radius(float new_radius);
	float get_brightness() const;
	void set_brightness(float new_brightness);
	Color get_color() const;
	void set_color(Color new_color);
};