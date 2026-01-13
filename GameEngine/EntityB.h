#pragma once

#include "Entity.h"
#include "CircleCollisionComponent.h"

class EntityB :public Entity
{
private:
	CircleCollisionComponent* collision;
public:
	EntityB()
	{
		collision = new CircleCollisionComponent(this, true, transform, FVector(100.f, 100.f));
		collision->on_overlap.bind(this, &EntityB::collision_test);
		collision->init();
	}
	CircleCollisionComponent* get_collision() const
	{
		return collision;
	}
	void collision_test(Entity* thisEntity, CollisionComponent* thisCollision, Entity* otherEntity, CollisionComponent* otherCollision)
	{
		std::cout << "B colliding" << std::endl;
	}
};