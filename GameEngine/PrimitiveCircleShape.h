#pragma once

#include "PrimitiveShape.h"

class PrimitiveCircleShape :public PrimitiveShape
{
private:
	FVector radius = FVector(0.f, 0.f);
public:
	PrimitiveCircleShape(FVector radius, Transform transform, Color fillColor = Color(0, 0, 0, 0), Color outlineColor = Color(255, 255, 255, 255));
	operator sf::Drawable*() const override
	{
		sf::CircleShape* circle = static_cast<sf::CircleShape*>(shape);
		circle->setFillColor(fillColor);
		circle->setOutlineThickness(0.05f);
		circle->setOutlineColor(outlineColor);
		circle->setRadius(1.f);
		circle->setOrigin(FVector(1.f, 1.f));
		circle->setPosition(transform.position);
		circle->setScale(radius.component_wise_mult(transform.scale));
		circle->setRotation(sf::radians(transform.forward.angle()));
		return circle;
	}

	const FVector& get_radius() const;
	void set_radius(const FVector& radius);
};