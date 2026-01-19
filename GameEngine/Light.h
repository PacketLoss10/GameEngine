#pragma once

#include "RenderComponent.h"
#include "Color.h"

class Light :public RenderComponent
{
private:
	float radius = 0.f;
	float brightness = 0.f;
	Color color = Color();
public:
	Light() = default;
	Light(Entity* owner, bool enabled, Transform transform, float radius, float brightness, Color color);

	void init() override;

	float get_radius() const;
	void set_radius(float radius);

	float get_brightness() const;
	void set_brightness(float brightness);

	const Color& get_color() const;
	void set_color(const Color& color);
};