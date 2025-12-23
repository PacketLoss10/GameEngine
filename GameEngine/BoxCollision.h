#pragma once

#include "CollisionArea.h"

class BoxCollision :public CollisionArea 
{
private:
	FVector size = FVector(0.f, 0.f);
public:
	BoxCollision();
	BoxCollision(FVector size, FVector position, Color fillColor, Color outlineColor, bool visible);
	bool is_overlapping(CollisionArea* other) const override;
	bool contains_point(const FVector& point) const override;
	void render() const override;
	const FVector& get_size() const;
	void set_size(const FVector& new_size);
};