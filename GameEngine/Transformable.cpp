#include "Transformable.h"

Transformable::Transformable(Transform transform) :transform(transform) {}

const Transform& Transformable::get_transform() const
{
	return transform;
}

void Transformable::set_transform(const Transform& transform)
{
	this->transform = transform;
}

const FVector& Transformable::get_position() const
{
	return transform.position;
}

void Transformable::set_position(const FVector& position)
{
	transform.position = position;
}

void Transformable::move_by(const FVector& step)
{
	transform.position = transform.position + step;
}

const FVector& Transformable::get_forward() const
{
	return transform.forward;
}

void Transformable::set_forward(const FVector& forward)
{
	transform.forward = forward;
}

float Transformable::get_rotation() const
{
	return transform.forward.angle();
}

void Transformable::set_rotation(float rotation)
{
	transform.forward = FVector(cosf(rotation), sinf(rotation));
}

void Transformable::rotate_by(float angle)
{
	transform.forward = transform.forward.rotated_by(angle);
}

const FVector& Transformable::get_scale() const
{
	return transform.scale;
}

void Transformable::set_scale(const FVector& scale)
{
	transform.scale = scale;
}