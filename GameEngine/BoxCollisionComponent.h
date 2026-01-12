#pragma once

#include "CollisionComponent.h"

class BoxCollisionComponent :public CollisionComponent
{
private:
	FVector size = FVector();
public:
	BoxCollisionComponent() = default;
	BoxCollisionComponent(FVector position, FVector size);

	void init(Entity* owner, bool enabled, FVector position, FVector size);

	const FVector& get_size() const;
	void set_size(const FVector& size);
};
