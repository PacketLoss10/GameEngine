#pragma once

#include "Transform.h"

class Transformable
{
protected:
	Transform transform = Transform();
public:
	Transformable() = default;
	Transformable(Transform transform);
	virtual ~Transformable() = default;

	const Transform& get_transform() const;
	void set_transform(const Transform& transform);

	const FVector& get_position() const;
	void set_position(const FVector& new_position);

	const FVector& get_forward() const;
	void set_forward(const FVector& new_forward);

	const FVector& get_scale() const;
	void set_scale(const FVector& new_scale);
};