#pragma once

#include "ComponentManager.h"
#include "CollisionComponent.h"
#include "CircleCollisionComponent.h"
#include "BoxCollisionComponent.h"

#define COLLISION_COMPONENT_MANAGER CollisionComponentManager::instance()

class CollisionComponentManager :public ComponentManager<CollisionComponent>
{
private:
	CollisionComponentManager() = default;
	CollisionComponentManager(const CollisionComponentManager&) = delete;
	CollisionComponentManager& operator=(const CollisionComponentManager&) = delete;

	void box_on_box(BoxCollisionComponent* boxA, BoxCollisionComponent* boxb);
	void circle_on_circle(CircleCollisionComponent* circleA, CircleCollisionComponent* circleB);
	void circle_on_box(CircleCollisionComponent* circle, BoxCollisionComponent* box);
	FVector perpendicular(const FVector& v) const;
public:
	static CollisionComponentManager& instance();
	void update();
};