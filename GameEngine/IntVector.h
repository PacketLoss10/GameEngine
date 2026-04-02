#pragma once

#include <SFML/System/Vector2.hpp>

class IntVector
{
public:
	int x = 0;
	int y = 0;

	IntVector() = default;
	IntVector(int x, int y);

	operator sf::Vector2i() const
	{
		return sf::Vector2i(x, y);
	}

	IntVector operator+(const IntVector& other) const
	{
		return IntVector(x + other.x, y + other.y);
	}
	IntVector operator-(const IntVector& other) const
	{
		return IntVector(x - other.x, y - other.y);
	}
	IntVector operator*(int other) const
	{
		return IntVector(x * other, y * other);
	}
	IntVector operator/(int other) const
	{
		return IntVector(x / other, y / other);
	}

	int dot(const IntVector& other) const;
	int cross(const IntVector& other) const;

	IntVector component_wise_mult(const IntVector& other) const;
	IntVector component_wise_div(const IntVector& other) const;
};