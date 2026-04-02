#pragma once

#include "Component.h"
#include "CollisionComponent.h"
#include "Delegate.h"

class DragDropComponent :public Component
{
private:
	CollisionComponent* geometry = nullptr;

	int layer = 0;

	Vector2 dragStartMousePos;
	Vector2 dragStartEntityPos;
	Vector2 dragOffset;
public:
	Delegate<const Vector2&> on_drag;
	Delegate<const Vector2&> on_drag_begin;
	Delegate<const Vector2&> on_drag_end;

	Delegate<const Vector2&> on_hover;
	Delegate<const Vector2&> on_hover_begin;
	Delegate<const Vector2&> on_hover_end;

	DragDropComponent(Entity* owner);
	virtual ~DragDropComponent() = default;

	virtual void finalise() override;

	CollisionComponent* get_geometry() const;
	void set_geometry(CollisionComponent* geometry);

	int get_layer() const;
	void set_layer(int layer);

	const Vector2& get_dragStartMousePos() const;
	void set_dragStartMousePos(const Vector2& dragStartMousePos);

	const Vector2& get_dragStartEntityPos() const;
	void set_dragStartEntityPos(const Vector2& dragStartEntityPos);

	const Vector2& get_dragOffset() const;
	void set_dragOffset(const Vector2& dragOffset);
};