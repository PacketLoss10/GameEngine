#pragma once

#include "Vector2.h"

class Transform
{
public:
	Vector2 position = Vector2(0.f, 0.f);
	Vector2 forward = Vector2(1.f, 0.f);
	Vector2 scale = Vector2(1.f, 1.f);

	static Transform identity;

	Transform() = default;
	Transform(Vector2 position, Vector2 forward, Vector2 scale);
};