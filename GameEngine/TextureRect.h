#pragma once

#include "Transform.h"

class TextureRect
{
private:
	IVector position = IVector(0, 0);
	IVector size = IVector(1, 1);
public:
	TextureRect() = default;
	TextureRect(IVector position, IVector size);
	operator sf::IntRect() const
	{
		return sf::IntRect(position, size);
	}
};