#pragma once

#include "RenderComponent.h"

class LightComponent :public RenderComponent
{
private:
	float radius = 100.f;
	float brightness = 1.f;
	Color color = Color(255, 255, 255, 255);
public:
	LightComponent(Entity* owner);
	virtual ~LightComponent() = default;

	RenderDataType get_type() const override;
	LightRenderData build_render_data() const;

	float get_radius() const;
	void set_radius(float radius);

	float get_brightness() const;
	void set_brightness(float brightness);

	const Color& get_color() const;
	void set_color(const Color& color);
};