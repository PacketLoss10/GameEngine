#pragma once

#include "EngineUtils.h"
#include "GameWindow.h"

class CollisionArea 
{
protected:
	FVector position = FVector(0.f, 0.f);
	Color fillColor = Color(0, 0, 0, 0);
	Color outlineColor = Color(255, 255, 255, 255);
	bool visible = false;
public:
	CollisionArea();
	CollisionArea(FVector position, Color fillColor, Color outlineColor, bool visible);
	virtual bool is_overlapping(CollisionArea* other) const = 0;
	virtual bool contains_point(const FVector& point) const = 0;
	virtual void render() const = 0;
	const FVector& get_position() const;
	void set_position(const FVector& new_position);
	const Color& get_fillColor() const;
	void set_fillColor(const Color& new_fillColor);
	const Color& get_outlineColor() const;
	void set_outlineColor(const Color& new_outlineColor);
	bool is_visible() const;
	void set_visible(bool new_visible);
};