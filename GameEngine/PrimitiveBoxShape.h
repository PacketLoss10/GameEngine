#pragma once

#include "PrimitiveShape.h"

class PrimitiveBoxShape :public PrimitiveShape
{
private:
	FVector size = FVector(0.f, 0.f);
public:
	PrimitiveBoxShape(FVector size, Transform transform, Color fillColor = Color(0, 0, 0, 0), Color outlineColor = Color(255, 255, 255, 255));
	operator sf::Drawable*() const override
	{
		sf::RectangleShape* box = static_cast<sf::RectangleShape*>(shape);
		box->setFillColor(fillColor);
		box->setOutlineThickness(0.05f);
		box->setOutlineColor(outlineColor);
		box->setSize(size);
		box->setOrigin(size / 2.f);
		box->setPosition(transform.position);
		box->setScale(transform.scale);
		box->setRotation(sf::radians(transform.forward.angle()));
		return box;
	}

	const FVector& get_size() const;
	void set_size(const FVector& size);
};