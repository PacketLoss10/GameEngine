#pragma once

#include "SFML/Graphics.hpp"

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