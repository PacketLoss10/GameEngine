#pragma once

#include "Entity.h"
#include "CircleCollisionComponent.h"

class EntityB :public Entity
{
private:
	CircleCollisionComponent* collision = new CircleCollisionComponent;
public:
	EntityB()
	{
		collision->init(this, true, transform.position, 100.f);
		collision->on_overlap.bind(this, &EntityB::collision_test);
	}
	CollisionComponent* get_collision() const
	{
		return collision;
	}
	void collision_test(Entity* thisEntity, CollisionComponent* thisCollision, Entity* otherEntity, CollisionComponent* otherCollision)
	{
		std::cout << "B colliding" << std::endl;
	}
};