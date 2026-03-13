#pragma once

#include "SFML/Graphics.hpp"

class Vector2
{
public:
	float x = 0.f;
	float y = 0.f;

	Vector2() = default;
	Vector2(float x, float y);

	operator sf::Vector2f() const
	{
		return sf::Vector2f(x, y);
	}

	bool operator==(const Vector2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	Vector2 operator+(const Vector2& rhs) const
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2 operator-(const Vector2& rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2 operator*(float rhs) const
	{
		return Vector2(x * rhs, y * rhs);
	}

	Vector2 operator/(float rhs) const
	{
		return Vector2(x / rhs, y / rhs);
	}

	float dot(const Vector2& rhs) const;

	float cross(const Vector2& rhs) const;

	Vector2 component_wise_mult(const Vector2& rhs) const;

	Vector2 component_wise_div(const Vector2& rhs) const;

	float size() const;

	float size_squared() const;

	Vector2 normalised() const;

	Vector2 perpendicular() const;

	float angle() const;

	Vector2 rotated_by(float angle) const;
};