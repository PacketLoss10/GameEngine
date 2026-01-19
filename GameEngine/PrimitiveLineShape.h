#pragma once

#include "PrimitiveShape.h"

class PrimitiveLineShape :public PrimitiveShape
{
private:
	float length = 0.f;
	float thickness = 5.f;
public:
	PrimitiveLineShape(float length, float thickness, Transform transform, Color color = Color(255, 255, 255, 255));
	operator sf::Drawable*() const
	{
		sf::RectangleShape* line = static_cast<sf::RectangleShape*>(shape);
		line->setFillColor(fillColor);
		line->setSize(FVector(length, thickness));
		line->setOrigin(line->getSize() / 2.f);
		line->setPosition(transform.position);
		line->setRotation(sf::radians(transform.forward.angle()));
		return line;
	}

	float get_length() const;
	void set_length(float length);

	float get_thickness() const;
	void set_thickness(float thickness);
};