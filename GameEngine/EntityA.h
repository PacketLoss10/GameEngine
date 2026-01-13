#pragma once

#include "Entity.h"
#include "CircleCollisionComponent.h"

class EntityA :public Entity
{
private:
	CircleCollisionComponent* collision;
public:
	EntityA()
	{
		collision = new CircleCollisionComponent(this, true,Transform(FVector(300.f,300.f),FVector(1.f,0.f),FVector(1.f,1.f)), FVector(200.f, 100.f));
		collision->on_overlap.bind(this, &EntityA::collision_test);
		collision->init();
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