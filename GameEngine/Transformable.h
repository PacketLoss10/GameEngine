#pragma once

#include "Transform.h"

class Transformable
{
protected:
	Transform transform;
public:
	Transformable(Transform transform) :transform(transform) {}
	virtual ~Transformable() = default;

	const Transform& get_transform() const
	{
		return transform;
	}

	void set_transform(const Transform& new_transform)
	{
		transform = new_transform;
	}

	const FVector& get_position() const
	{
		return transform.position;
	}

	void set_position(const FVector& new_position)
	{
		transform.position = new_position;
	}

	const FVector& get_forward() const
	{
		return transform.forward;
	}

	void set_forward(const FVector& new_forward)
	{
		transform.forward = new_forward;
	}

	const FVector& get_scale() const
	{
		return transform.scale;
	}

	void set_scale(const FVector& new_scale)
	{
		transform.scale = new_scale;
	}
};