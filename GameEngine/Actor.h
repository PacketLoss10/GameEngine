#pragma once

#include "EngineUtils.h"
#include "Renderer.h"
#include "CollisionArea.h"
#include "Sprite.h"

class Actor
{
protected:
	Transform transform = Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(1.f, 1.f));
	Renderable* renderable = nullptr;
	CollisionArea* collision = nullptr;
	bool toCull = false;
public:
	Actor(Transform transform, Renderable* renderable = nullptr);
	~Actor();
	virtual void update();
	const Transform& get_transform() const;
	void set_transform(const Transform& new_transform);
	void set_position(const FVector& new_position);
	void set_forward(const FVector& new_forward);
	void set_scale(const FVector& new_scale);
	CollisionArea* get_collision() const;
	Renderable* get_renderable() const;
	void set_collision(CollisionArea* new_collision);
	bool is_toCull() const;
	void set_toCull(bool new_toCull);
};