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
};

