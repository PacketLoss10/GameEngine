#pragma once

#include "EngineUtils.h"

class Renderable
{
private:
	Transform transform;
public:
	Renderable(Transform transform);
	virtual ~Renderable() = default;
	const Transform& get_transform() const;
	void set_transform(const Transform& new_transform);
	void set_position(const FVector& new_position);
	void set_forward(const FVector& new_forward);
	void set_scale(const FVector& new_scale);
};