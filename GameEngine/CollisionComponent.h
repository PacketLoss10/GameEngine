#pragma once

#include "Component.h"
#include "Transformable.h"
#include "Delegate.h"

class CollisionComponent :public Component, public Transformable
{
public:
	CollisionComponent() = default;
	CollisionComponent(Entity* owner, bool enabled, Transform transform);
	virtual ~CollisionComponent() = default;

	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_overlap;
};