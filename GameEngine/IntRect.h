#pragma once

#include "IntVector.h"
#include <SFML/Graphics/Rect.hpp>

class IntRect
{
public:
	IntVector position = IntVector();
	IntVector size = IntVector();

	IntRect() = default;
	IntRect(IntVector position, IntVector size);

	operator sf::IntRect() const
	{
		return sf::IntRect(sf::Vector2i(position.x, position.y), sf::Vector2i(size.x, size.y));
	}

	std::optional<IntRect> find_intersection(const IntRect& other) const;
};