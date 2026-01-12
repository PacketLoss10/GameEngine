#pragma once

#include "Component.h"
#include "Vector.h"
#include "Delegate.h"

class CollisionComponent :public Component
{
protected:
	FVector position = FVector();
public:
	CollisionComponent() = default;
	virtual ~CollisionComponent() = default;

	Delegate<Entity*, CollisionComponent*, Entity*, CollisionComponent*> on_overlap;

	const FVector& get_position() const;
	void set_position(const FVector& position);
};