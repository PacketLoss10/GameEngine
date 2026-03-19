#pragma once

#include "Component.h"
#include "CollisionComponent.h"

class DragDropComponent :public Component
{
private:
	CollisionComponent* geometry = nullptr;
	bool grabbed = false;
	Vector2 grabbedAt = Vector2(0.f, 0.f);
public:
	DragDropComponent(Entity* owner);
	virtual ~DragDropComponent() = default; 

	virtual void finalise() override;

	CollisionComponent* get_geometry() const;
	void set_geometry(CollisionComponent* geometry);
};