#include "Renderable.h"

Renderable::Renderable(Transform transform) :transform(transform) {}

const Transform& Renderable::get_transform() const
{
	return transform;
}

void Renderable::set_transform(const Transform& new_transform)
{
	transform = new_transform;
}

void Renderable::set_position(const FVector& new_position)
{
	transform.position = new_position;
}

void Renderable::set_forward(const FVector& new_forward)
{
	transform.forward = new_forward;
}

void Renderable::set_scale(const FVector& new_scale)
{
	transform.scale = new_scale;
}