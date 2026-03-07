#pragma once

#include "Component.h"
#include "Transformable.h"
#include "Delegate.h"

class CollisionComponent :public Component, public Transformable
{
public:
	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_overlap;
	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_begin_overlap;
	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_end_overlap;

	Delegate<Entity*, CollisionComponent*, const FVector&> on_mouse_overlap;
	Delegate<Entity*, CollisionComponent*, const FVector&> on_mouse_begin_overlap;
	Delegate<Entity*, CollisionComponent*, const FVector&> on_mouse_end_overlap;

	std::unordered_set<CollisionComponent*> overlaps;
	bool is_overlapping(CollisionComponent* overlap) const;
	void add_overlap(CollisionComponent* overlap);
	void remove_overlap(CollisionComponent* overlap);

	CollisionComponent() = default;
	CollisionComponent(Entity* owner, bool enabled, Transform transform);
	virtual ~CollisionComponent() = default;
};