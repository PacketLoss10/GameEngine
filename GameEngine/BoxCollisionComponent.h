#pragma once

#include "CollisionComponent.h"

class BoxCollisionComponent :public CollisionComponent
{
private:
	FVector size = FVector();
public:
	BoxCollisionComponent() = default;
	BoxCollisionComponent(Entity* owner, bool enabled, Transform transform, FVector size);

	void init() override;

	const FVector& get_size() const;
	void set_size(const FVector& size);
};
