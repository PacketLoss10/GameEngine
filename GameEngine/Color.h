#pragma once

#include "SFML/Graphics.hpp"

struct Color
{
public:
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	Color() = default;
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) :r(r), g(g), b(b), a(a) {}

	operator sf::Color() const
	{
		return sf::Color(static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g), static_cast<std::uint8_t>(b), static_cast<std::uint8_t>(a));
	}
};