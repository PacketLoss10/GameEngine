#pragma once

#include "Component.h"
#include "Delegate.h"

class CollisionComponent :public Component
{
public:
	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_overlap;
	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_begin_overlap;
	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_end_overlap;

	Delegate<Entity*, CollisionComponent*, const Vector2&> on_mouse_overlap;
	Delegate<Entity*, CollisionComponent*, const Vector2&> on_mouse_begin_overlap;
	Delegate<Entity*, CollisionComponent*, const Vector2&> on_mouse_end_overlap;

	std::unordered_set<CollisionComponent*> overlaps;
	bool is_overlapping(CollisionComponent* overlap) const;
	void add_overlap(CollisionComponent* overlap);
	void remove_overlap(CollisionComponent* overlap);

	bool mouseOverlapping = false;
	bool is_mouseOverlapping() const;
	void set_mouseOverlapping(bool mouseOverlapping);

	CollisionComponent(Entity* owner);
	virtual ~CollisionComponent() = default;

	virtual void finalise() override;
};