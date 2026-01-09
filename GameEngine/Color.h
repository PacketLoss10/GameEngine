#pragma once

#include "SLObject.h"
#include "SFML/Graphics.hpp"

class Color: public SLObject
{
public:
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 255;

	Color() {}
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) :r(r), g(g), b(b), a(a) {}

	operator sf::Color() const
	{
		return sf::Color(static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g), static_cast<std::uint8_t>(b), static_cast<std::uint8_t>(a));
	}

	TO_JSON(
		json.set("r", r);
	json.set("g", g);
	json.set("b", b);
	json.set("a", a);
		)

		FROM_JSON(
			r = json.get("r");
	g = json.get("g");
	b = json.get("b");
	a = json.get("a");
		)
};