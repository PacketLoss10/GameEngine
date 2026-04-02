#pragma once

#include "RenderComponent.h"
#include "ZSortable.h"
#include "Vector2.h"
#include "Color.h"

class PrimitiveCircleComponent :public RenderComponent, public ZSortable
{
private:
	Vector2 radius = Vector2();
	Color fillColor = Color();
	Color outlineColor = Color();
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

	bool is_lit() const;
	void set_lit(bool lit);
};