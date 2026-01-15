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
	void set_position(const FVector& position);
	void move_by(const FVector& step);

	const FVector& get_forward() const;
	void set_forward(const FVector& forward);

	float get_rotation() const;
	void set_rotation(float rotation);
	void rotate_by(float angle);

	const FVector& get_scale() const;
	void set_scale(const FVector& scale);
};