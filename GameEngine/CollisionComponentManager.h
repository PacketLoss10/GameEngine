#pragma once

#include "ComponentManager.h"
#include "CollisionComponent.h"
#include "CircleCollisionComponent.h"
#include "BoxCollisionComponent.h"
#include "Rect.h"

#define COLLISION_COMPONENT_MANAGER CollisionComponentManager::instance()

class CollisionComponentManager :public ComponentManager<CollisionComponent>
{
private:
	CollisionComponentManager() = default;
	CollisionComponentManager(const CollisionComponentManager&) = delete;
	CollisionComponentManager& operator=(const CollisionComponentManager&) = delete;
public:
	static CollisionComponentManager& instance();
	void update();
};