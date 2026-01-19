#pragma once

#include "Entity.h"
#include "CircleCollisionComponent.h"
#include "BoxCollisionComponent.h"
#include "Light.h"
#include "Sprite.h"

class EntityA :public Entity
{
private:
	CircleCollisionComponent* collision;
	Light* light;
	Sprite* sprite;
public:
	EntityA()
	{
		collision = new CircleCollisionComponent(this, true, Transform(FVector(300.f, 300.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), FVector(200.f, 100.f));
		collision->on_overlap.bind(this, &EntityA::collision_test);
		collision->init();

		light = new Light(this, true, transform, 200.f, 1.f, Color(255, 255, 255));
		light->init();

		sprite = new Sprite(this, true, Texture("NULLTEXTURE.png"), TextureRect(IVector(0, 0), IVector(420, 420)), 1, transform);
		sprite->init();
	}
	CircleCollisionComponent* get_collision()
	{
		return collision;
	}
	Light* get_light()
	{
		return light;
	}
	Sprite* get_sprite()
	{
		return sprite;
	}
	void collision_test(Entity* thisEntity, CollisionComponent* thisCollision, Entity* otherEntity, CollisionComponent* otherCollision)
	{
		std::cout << "A colliding" << std::endl;
	}
};