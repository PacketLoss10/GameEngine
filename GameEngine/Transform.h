#pragma once

#include "SFML/Graphics.hpp"

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

struct FVector
{
	float x = 0.f;
	float y = 0.f;

	FVector() = default;
	FVector(float x, float y) :x(x), y(y) {}

	operator sf::Vector2f() const
	{
		return sf::Vector2f(x, y);
	}

	FVector operator+(const FVector& other) const
	{
		return FVector(x + other.x, y + other.y);
	}
	FVector operator-(const FVector& other) const
	{
		return FVector(x - other.x, y - other.y);
	}
	FVector operator*(float other) const
	{
		return FVector(x * other, y * other);
	}
	FVector operator/(float other) const
	{
		return FVector(x / other, y / other);
	}

	float dot(const FVector& other) const
	{
		return x * other.x + y * other.y;
	}
	float cross(const FVector& other) const
	{
		return x * other.y - y * other.x;
	}

	FVector component_wise_mult(const FVector& other) const
	{
		return FVector(x * other.x, y * other.y);
	}
	FVector component_wise_div(const FVector& other) const
	{
		return FVector(x / other.x, y / other.y);
	}

	float size() const
	{
		return std::sqrtf(x * x + y * y);
	}
	float size_squared() const
	{
		return x * x + y * y;
	}

	FVector normalised() const
	{
		return *this / size();
	}

	float angle() const
	{
		return std::atan2f(y, x);
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

struct FRect
{
	FVector position = FVector();
	FVector size = FVector();

	FRect() = default;
	FRect(FVector position, FVector size) :position(position), size(size) {}

	operator sf::FloatRect() const
	{
		return sf::FloatRect(sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y));
	}

	std::optional<FRect> find_intersection(const FRect& other) const
	{
		float x = std::max(position.x, other.position.x);
		float y = std::max(position.y, other.position.y);
		float w = std::min(position.x + size.x, other.position.x + other.size.x) - x;
		float h = std::min(position.y + size.y, other.position.y + other.size.y) - y;

		if (w <= 0 || h <= 0)
			return std::nullopt;

		return FRect(FVector(x, y), FVector(w, h));
	}

	bool contains_point(const FVector& point) const
	{
		return point.x >= position.x && point.x <= position.x + size.x &&
			point.y >= position.y && point.y <= position.y + size.y;
	}
};

struct Transform
{
	FVector position = FVector(0.f, 0.f);
	FVector forward = FVector(1.f, 0.f);
	FVector scale = FVector(1.f, 1.f);

	Transform() = default;
	Transform(FVector position, FVector forward, FVector scale) :position(position), forward(forward), scale(scale) {}
};