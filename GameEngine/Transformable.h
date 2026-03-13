#pragma once

#include "Transform.h"

class Transformable
{
protected:
	Vector2 origin = Vector2(0.f, 0.f);
	Transform transform = Transform();
public:
	Transformable() = default;
	Transformable(Transform transform);
	virtual ~Transformable() = default;

	const Transform& get_transform() const;
	void set_transform(const Transform& transform);

	const Vector2& get_origin() const;
	void set_origin(const Vector2& origin);

	const Vector2& get_position() const;
	void set_position(const Vector2& position);
	void move_by(const Vector2& step);

	const Vector2& get_forward() const;
	void set_forward(const Vector2& forward);

	float get_rotation() const;
	void set_rotation(float rotation);
	void rotate_by(float angle);

	const Vector2& get_scale() const;
	void set_scale(const Vector2& scale);
	void scale_by(const Vector2& factor);
};