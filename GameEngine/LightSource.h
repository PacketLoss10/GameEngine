#pragma once

#include "Actor.h"
#include "EngineUtils.h"

class LightSource: public Actor
{
private:
	float radius;
	float brightness;
	Color color;
public:
	LightSource(FVector position, float radius, float brightness, Color color) :Actor(Transform(position, FVector(1.f, 0.f), FVector(0.f, 0.f))), radius(radius), brightness(brightness), color(color) {}
	void update() override;
	float get_radius() const;
	void set_radius(float new_radius);
	float get_brightness() const;
	void set_brightness(float new_brightness);
	Color get_color() const;
	void set_color(Color new_color);
};