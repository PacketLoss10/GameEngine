#pragma once

#include "CollisionComponent.h"

class CircleCollisionComponent :public CollisionComponent
{
private:
	Vector2 radius = Vector2(0.f, 0.f);
public:
	CircleCollisionComponent(Entity* owner);
	virtual ~CircleCollisionComponent() = default;

	const Vector2& get_radius() const;
	void set_radius(const Vector2& radius);
};