#pragma once

#include "RenderComponent.h"
#include "ZSortable.h"
#include "Color.h"

class PrimitiveCircleComponent :public RenderComponent, public ZSortable
{
private:
	Vector2 radius = Vector2();
	Color fillColor = Color();
	Color outlineColor = Color();
	float outlineThickness = 1.f;
	bool lit = false;
public:
	PrimitiveCircleComponent(Entity* owner);
	virtual ~PrimitiveCircleComponent() = default;

	RenderDataType get_type() const override;
	PrimitiveRenderData build_render_data() const;

	const Vector2& get_radius() const;
	void set_radius(const Vector2& radius);

	const Color& get_fillColor() const;
	void set_fillColor(const Color& fillColor);

	const Color& get_outlineColor() const;
	void set_outlineColor(const Color& outlineColor);

	float get_outlineThickness() const;
	void set_outlineThickness(float outlineThickness);

	bool is_lit() const;
	void set_lit(bool lit);
};