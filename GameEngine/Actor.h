#pragma once

#include "EngineUtils.h"

class Actor
{
private:
	Transform transform;
	bool toCull = false;
public:
	Actor(Transform transform);
	~Actor();
	virtual void update() = 0;
	const Transform& get_transform() const;
	void set_transform(const Transform& new_transform);
	void set_position(const FVector& new_position);
	void set_forward(const FVector& new_forward);
	void set_scale(const FVector& new_scale);
	bool is_toCull() const;
	void set_toCull(bool new_toCull);
};