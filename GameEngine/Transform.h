#pragma once

#include "Matrix.h"
#include "Vector2.h"

namespace mth
{
	const float pi = 3.14159f;
};

struct IVector
{
	int x = 0;
	int y = 0;

	IVector() = default;
	IVector(int x, int y) :x(x), y(y) {}

	operator sf::Vector2i() const
	{
		return sf::Vector2i(x, y);
	}

	IVector operator+(const IVector& other) const
	{
		return IVector(x + other.x, y + other.y);
	}
	IVector operator-(const IVector& other) const
	{
		return IVector(x - other.x, y - other.y);
	}
	IVector operator*(int other) const
	{
		return IVector(x * other, y * other);
	}
	IVector operator/(int other) const
	{
		return IVector(x / other, y / other);
	}

	int dot(const IVector& other) const
	{
		return x * other.x + y * other.y;
	}
	int cross(const IVector& other) const
	{
		return x * other.y - y * other.x;
	}

	IVector component_wise_mult(const IVector& other) const
	{
		return IVector(x * other.x, y * other.y);
	}
	IVector component_wise_div(const IVector& other) const
	{
		return IVector(x / other.x, y / other.y);
	}
};

struct IRect
{
	IVector position = IVector();
	IVector size = IVector();

	IRect() = default;
	IRect(IVector position, IVector size) :position(position), size(size) {}

	operator sf::IntRect() const
	{
		return sf::IntRect(sf::Vector2i(position.x, position.y), sf::Vector2i(size.x, size.y));
	}

	std::optional<IRect> find_intersection(const IRect& other) const
	{
		int x = std::max(position.x, other.position.x);
		int y = std::max(position.y, other.position.y);
		int w = std::min(position.x + size.x, other.position.x + other.size.x) - x;
		int h = std::min(position.y + size.y, other.position.y + other.size.y) - y;

		if (w <= 0 || h <= 0)
			return std::nullopt;

		return IRect(IVector(x, y), IVector(w, h));
	}
};

//struct FRect
//{
//	Vector2 position = Vector2();
//	Vector2 size = Vector2();
//
//	FRect() = default;
//	FRect(Vector2 position, Vector2 size) :position(position), size(size) {}
//
//	operator sf::FloatRect() const
//	{
//		return sf::FloatRect(sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y));
//	}
//
//	std::optional<FRect> find_intersection(const FRect& other) const
//	{
//		float x = std::max(position.x, other.position.x);
//		float y = std::max(position.y, other.position.y);
//		float w = std::min(position.x + size.x, other.position.x + other.size.x) - x;
//		float h = std::min(position.y + size.y, other.position.y + other.size.y) - y;
//
//		if (w <= 0 || h <= 0)
//			return std::nullopt;
//
//		return FRect(Vector2(x, y), Vector2(w, h));
//	}
//
//	bool contains_point(const Vector2& point) const
//	{
//		return point.x >= position.x && point.x <= position.x + size.x &&
//			point.y >= position.y && point.y <= position.y + size.y;
//	}
//};

class Transform
{
public:
	Vector2 position = Vector2(0.f, 0.f);
	Vector2 forward = Vector2(1.f, 0.f);
	Vector2 scale = Vector2(1.f, 1.f);

	static Transform identity;

	Transform() = default;
	Transform(Vector2 position, Vector2 forward, Vector2 scale);
	Transform(Matrix matrix);
};