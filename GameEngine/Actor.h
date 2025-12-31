#pragma once

#include "EngineUtils.h"
#include "Renderer.h"
#include "CollisionArea.h"
#include "Sprite.h"

#define SETUP_ACTOR(derivedClass) \
public: Delegate<derivedClass, const Actor*, const Actor*> on_overlap;

class Actor
{
protected:
	Transform transform;
	Sprite* sprite = nullptr;
	CollisionArea* collision = nullptr;
	bool toCull = false;
public:
	Actor(Transform transform, Sprite* sprite = nullptr);
	~Actor();
	virtual void update() {};
	virtual void render();
	const Transform& get_transform() const;
	void set_transform(const Transform& new_transform);
	void set_position(const FVector& new_position);
	void set_forward(const FVector& new_forward);
	void set_scale(const FVector& new_scale);
	CollisionArea* get_collision() const;
	Sprite* get_sprite() const;
	void set_collision(CollisionArea* new_collision);
	bool is_toCull() const;
	void set_toCull(bool new_toCull);
};