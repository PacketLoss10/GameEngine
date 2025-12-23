#pragma once

#include "SFML/Graphics.hpp"
#include "unordered_map"
#include "concepts"
#include "functional"
#include "iostream"
#include "fstream"
#include "vector"
#include "math.h"

template<typename T>
concept VectorConcept = std::same_as<T, int> || std::same_as<T, float>;

template<VectorConcept T>
class Vector
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

	operator std::string() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
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
};

using IVector = Vector<int>;
using FVector = Vector<float>;

template<VectorConcept T>
class Rect
{
public:
	Vector<T> position = Vector<T>(0, 0);
	Vector<T> size = Vector<T>(0, 0);

	Rect() {}
	Rect(Vector<T> position, Vector<T> size) :position(position), size(size) {}

	operator sf::Rect<T>() const
	{
		return sf::Rect<T>(position, size);
	}

	std::optional<Rect<T>> find_intersection(const Rect<T>& other) const
	{
		T x = std::max(position.x, other.position.x);
		T y = std::max(position.y, other.position.y);
		T w = std::min(position.x + size.x, other.position.x + other.size.x) - x;
		T h = std::min(position.y + size.y, other.position.y + other.size.y) - y;

		if (w <= 0 || h <= 0)
			return std::nullopt;

		return Rect<T>(Vector<T>(x, y), Vector<T>(w, h));
	}

	bool contains_point(const FVector& point) const
	{
		return point.x >= position.x && point.x <= position.x + size.x &&
			point.y >= position.y && point.y <= position.y + size.y;
	}
};

using IRect = Rect<int>;
using FRect = Rect<float>;

class Transform
{
public:
	FVector position = FVector(0.f, 0.f);
	FVector forward = FVector(1.f, 0.f);
	FVector scale = FVector(1.f, 1.f);

	Transform() {}
	Transform(FVector position, FVector forward, FVector scale) :position(position), forward(forward), scale(scale) {}
};

class Color
{
public:
	std::uint8_t r = 0;
	std::uint8_t g = 0;
	std::uint8_t b = 0;
	std::uint8_t a = 255;

	Color() {}
	Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255) :r(r), g(g), b(b), a(a) {}

	operator sf::Color() const
	{
		return sf::Color(r, g, b, a);
	}
};