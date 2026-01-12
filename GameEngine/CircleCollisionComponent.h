#pragma once

#include "CollisionComponent.h"

class CircleCollisionComponent :public CollisionComponent
{
private:
	float radius;
public:
	CircleCollisionComponent() = default;
	CircleCollisionComponent(FVector position, float radius);

	float get_radius() const;
	void set_radius(float radius);
};