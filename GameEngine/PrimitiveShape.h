#pragma once

#include "Transformable.h"
#include "Color.h"

class PrimitiveShape :public Transformable
{
protected:
	sf::Drawable* shape = nullptr;
	Color fillColor = Color(0, 0, 0, 0);
	Color outlineColor = Color(255, 255, 255, 255);

public:
	PrimitiveShape(sf::Drawable* shape, Transform transform, Color fillColor, Color outlineColor);
	virtual ~PrimitiveShape();
	virtual operator sf::Drawable* () const = 0;

	const Color& get_fillColor() const;
	void set_fillColor(const Color& fillColor);

	const Color& get_outlineColor() const;
	void set_outlineColor(const Color& outlineColor);
};