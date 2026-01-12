#pragma once

#include "Entity.h"
#include "CircleCollisionComponent.h"

class EntityA :public Entity
{
private:
	CircleCollisionComponent* collision = new  CircleCollisionComponent(FVector(0.f,0.f), 100.f);
public:
	EntityA()
	{
		collision->on_overlap.bind(this, &EntityA::collision_test);
	}
	CircleCollisionComponent* get_collision() const
	{
		return collision;
	}
	void collision_test(Entity* thisEntity, CollisionComponent* thisCollision, Entity* otherEntity, CollisionComponent* otherCollision)
	{
		std::cout << "A colliding" << std::endl;
	}
};