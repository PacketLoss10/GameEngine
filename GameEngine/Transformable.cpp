#include "Transformable.h"
#include "Matrix.h"

Transformable::Transformable(Transform transform) :transform(transform) {}

const Transform& Transformable::get_transform() const
{
	return transform;
}

void Transformable::set_transform(const Transform& transform)
{
	this->transform = transform;
}

const Vector2& Transformable::get_origin() const
{
	return origin;
}

void Transformable::set_origin(const Vector2& origin)
{
	this->origin = origin;
}

const Vector2& Transformable::get_position() const
{
	return transform.position;
}

void Transformable::set_position(const Vector2& position)
{
	Vector2 delta = position - transform.position;
	transform.position = position;
	origin = origin + delta;
}

void Transformable::move_by(const Vector2& step)
{
	transform.position = transform.position + step;
	origin = origin + step;
}

const Vector2& Transformable::get_forward() const
{
	return transform.forward;
}

void Transformable::set_forward(const Vector2& forward)
{
	Vector2 offset = transform.position - origin;
	offset = offset.rotated_by(forward.angle() - get_rotation());

	transform.forward = forward;
	transform.position = origin + offset;
}

float Transformable::get_rotation() const
{
	return transform.forward.angle();
}

void Transformable::set_rotation(float rotation)
{
	Vector2 offset = transform.position - origin;
	offset = offset.rotated_by(rotation - get_rotation());

	transform.forward = Vector2(cosf(rotation), sinf(rotation));
	transform.position = origin + offset;
}

void Transformable::rotate_by(float angle)
{
	Vector2 offset = transform.position - origin;
	offset = offset.rotated_by(angle);

	transform.forward = transform.forward.rotated_by(angle);
	transform.position = origin + offset;
}

const Vector2& Transformable::get_scale() const
{
	return transform.scale;
}

void Transformable::set_scale(const Vector2& scale)
{
	Vector2 offset = transform.position - origin;
	offset = offset.component_wise_mult(scale.component_wise_div(transform.scale));

	transform.scale = scale;
	transform.position = origin + offset;
}

void Transformable::scale_by(const Vector2& factor)
{
	Vector2 offset = transform.position - origin;
	offset = offset.component_wise_mult(factor);
	
	transform.scale = transform.scale.component_wise_mult(factor);
	transform.position = origin + offset;
}