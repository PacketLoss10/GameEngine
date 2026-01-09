#pragma once

#include "Vector.h"

template<VectorConcept T>
class Rect :public SLObject
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

	TO_JSON(
		json.set("position", position);
	json.set("size", size);
		)

		FROM_JSON(
			position = json.get("position");
	size = json.get("size");
		)
};

using IRect = Rect<int>;
using FRect = Rect<float>;