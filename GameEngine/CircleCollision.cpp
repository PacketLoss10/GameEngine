#include "CircleCollision.h"
#include "BoxCollision.h"

CircleCollision::CircleCollision() {}

CircleCollision::CircleCollision(float radius, FVector position, Color fillColor, Color outlineColor, bool visible) :radius(radius), CollisionArea(position, fillColor, outlineColor, visible) {}

bool CircleCollision::is_overlapping(CollisionArea* other) const
{
	if (auto circleCollision = dynamic_cast<const CircleCollision*>(other))
	{
		float r = radius + circleCollision->get_radius();
		return (position - circleCollision->get_position()).size_squared() <= r * r;
	}
	else if (auto boxCollision = dynamic_cast<const BoxCollision*>(other))
	{
		FVector min = boxCollision->get_position() - boxCollision->get_size() / 2.f;
		FVector max = boxCollision->get_position() + boxCollision->get_size() / 2.f;

		FVector clamped(
			std::max(min.x, std::min(position.x, max.x)),
			std::max(min.y, std::min(position.y, max.y)));

		return (position - clamped).size_squared() <= radius * radius;
	}
	else return false;
}

bool CircleCollision::contains_point(const FVector& point) const
{
	return (point - position).size_squared() < radius * radius;
}

void CircleCollision::render() const
{
	if (!visible) return;

	sf::CircleShape shape = sf::CircleShape(radius);
	shape.setPosition(position - FVector(radius, radius));
	shape.setFillColor(fillColor);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(outlineColor);

	GAME_WINDOW.render(shape, nullptr);
}

float CircleCollision::get_radius() const 
{
	return radius;
}

void CircleCollision::set_radius(float new_radius) 
{
	radius = new_radius; 
}