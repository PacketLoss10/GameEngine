#include "Actor.h"

Actor::Actor(Transform transform, Renderable* renderable) 
	:transform(transform),
	renderable(renderable) {}

Actor::~Actor() 
{
	delete renderable;
	delete collision;
}

void Actor::update()
{
	renderable->set_transform(transform);
}

const Transform& Actor::get_transform() const
{
	return transform;
}

void Actor::set_transform(const Transform& new_transform)
{
	transform = new_transform;
}

void Actor::set_position(const FVector& new_position)
{
	transform.position = new_position;
}

void Actor::set_forward(const FVector& new_forward)
{
	transform.forward = new_forward;
}

void Actor::set_scale(const FVector& new_scale)
{
	transform.scale = new_scale;
}

CollisionArea* Actor::get_collision() const
{
	return collision;
}

Renderable* Actor::get_renderable() const
{
	return renderable;
}

void Actor::set_collision(CollisionArea* new_collision)
{
	collision = new_collision;
}

bool Actor::is_toCull() const
{
	return toCull;
}

void Actor::set_toCull(bool new_toCull)
{
	toCull = new_toCull;
}