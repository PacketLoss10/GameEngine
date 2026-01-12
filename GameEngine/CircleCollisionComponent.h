#pragma once

#include "CollisionComponent.h"

class CircleCollisionComponent :public CollisionComponent
{
private:
	float radius = 0.f;
public:
	CircleCollisionComponent() = default;

	void init(Entity* owner, bool enabled, FVector position, float radius);

	float get_radius() const;
	void set_radius(float radius);
};