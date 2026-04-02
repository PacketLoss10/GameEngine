#pragma once

#include "CollisionComponent.h"

class BoxCollisionComponent :public CollisionComponent
{
private:
	Vector2 size = Vector2(0.f, 0.f);
public:
	BoxCollisionComponent(Entity* owner);
	virtual ~BoxCollisionComponent() = default;

	const Vector2& get_size() const;
	void set_size(const Vector2& size);
};