#pragma once

#include "SLObject.h"
#include "SFML/Graphics.hpp"

template<typename T>
concept VectorConcept = std::same_as<T, int> || std::same_as<T, float>;

template<VectorConcept T>
class Vector : public SLObject
{
public:
	T x = 0;
	T y = 0;

	Vector() {}
	Vector(T x, T y) :x(x), y(y) {}

	operator sf::Vector2<T>() const
	{
		return sf::Vector2<T>(x, y);
	}

	operator Vector<float>() const
	{
		return Vector<float>(static_cast<float>(x), static_cast<float>(y));
	}

	operator Vector<int>() const
	{
		return Vector<int>(static_cast<int>(x), static_cast<int>(y));
	}

	operator std::string() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	bool operator==(const Vector<T>& other) const
	{
		return x == other.x && y == other.y;
	}

	Vector<T> operator+(const Vector<T>& other) const
	{
		return Vector<T>(x + other.x, y + other.y);
	}

	Vector<T> operator-(const Vector<T>& other) const
	{
		return Vector<T>(x - other.x, y - other.y);
	}

	Vector<T> operator*(T other) const
	{
		return Vector<T>(x * other, y * other);
	}

	Vector<T> operator/(T other) const
	{
		return Vector<T>(static_cast<T>(x / other), static_cast<T>(y / other));
	}

	T dot(const Vector<T>& other) const
	{
		return x * other.x + y * other.y;
	}

	T cross(const Vector<T>& other) const
	{
		return x * other.y - y * other.x;
	}

	Vector<T> component_wise_mult(const Vector<T>& other) const
	{
		return Vector<T>(x * other.x, y * other.y);
	}

	Vector<T> component_wise_div(const Vector<T>& other) const
	{
		return Vector<T>(static_cast<T>(x / other.x), static_cast<T>(y / other.y));
	}

	float size() const
	{
		return std::sqrtf(static_cast<float>(x * x + y * y));
	}

	T size_squared() const
	{
		return x * x + y * y;
	}

	Vector<float> normalised() const
	{
		float length = size();
		return Vector<float>(static_cast<float>(x) / length, static_cast<float>(y) / length);
	}

	float angle() const
	{
		return std::atan2f(static_cast<float>(y), static_cast<float>(x));
	}

	TO_JSON(
		json.set("x", x);
	json.set("y", y);
		)

	FROM_JSON(
		x = json.get("x");
	y = json.get("y");
		)
};

using IVector = Vector<int>;
using FVector = Vector<float>;