#pragma once

#include "IntVector.h"
#include <SFML/Graphics/Rect.hpp>

class TextureRect
{
private:
	IntVector position = IntVector(0, 0);
	IntVector size = IntVector(1, 1);
public:
	TextureRect() = default;
	TextureRect(IntVector position, IntVector size);

	operator sf::IntRect() const
	{
		return sf::IntRect(position, size);
	}

	const IntVector& get_position() const;
	void set_position(const IntVector& position);

	const IntVector& get_size() const;
	void set_size(const IntVector& size);
};