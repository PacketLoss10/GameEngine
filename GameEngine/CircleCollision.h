#pragma once

#include "SLObject.h"
#include "CollisionArea.h"

class CircleCollision :public CollisionArea, public SLObject
{
private:
	float radius = 0.f;
public:
	CircleCollision();
	CircleCollision(float radius, FVector position, Color fillColor, Color outlineColor, bool visible);
	bool is_overlapping(CollisionArea* other) const override;
	bool contains_point(const FVector& point) const override;
	void render() const override;
	float get_radius() const;
	void set_radius(float new_radius);
	TO_JSON(
		json.set("position", position);
	json.set("radius", radius);
		)
		FROM_JSON(
			position = json.get("position");
	radius = json.get("radius");
		)
};