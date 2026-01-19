#pragma once

#include "CollisionComponent.h"

class CircleCollisionComponent :public CollisionComponent
{
private:
	FVector radius = FVector(0.f, 0.f);
public:
	CircleCollisionComponent() = default;
	CircleCollisionComponent(Entity* owner, bool enabled, Transform transform, FVector radius);

	void init() override;
	void render() override;

	const FVector& get_radius() const;
	void set_radius(const FVector& radius);
};