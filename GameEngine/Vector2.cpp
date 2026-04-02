#include "Vector2.h"

Vector2::Vector2(float x, float y) :x(x), y(y) {}

float Vector2::dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

float Vector2::cross(const Vector2& rhs) const
{
	return x * rhs.y - y * rhs.x;
}

Vector2 Vector2::component_wise_mult(const Vector2& rhs) const
{
	return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::component_wise_div(const Vector2& rhs) const
{
	return Vector2(x / rhs.x, y / rhs.y);
}

float Vector2::size() const
{
	return std::sqrtf(x * x + y * y);
}

float Vector2::size_squared() const
{
	return x * x + y * y;
}

Vector2 Vector2::normalised() const
{
	return *this / size();
}

Vector2 Vector2::perpendicular() const
{
	return Vector2(-y, x);
}

float Vector2::angle() const
{
	return std::atan2f(y, x);
}

Vector2 Vector2::rotated_by(float angle) const
{
	return Vector2(x * cosf(angle) - y * sinf(angle), x * sinf(angle) + y * cosf(angle));
}