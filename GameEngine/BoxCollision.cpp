#include "BoxCollision.h"
#include "CircleCollision.h"


BoxCollision::BoxCollision() {}

BoxCollision::BoxCollision(FVector size, FVector position, Color fillColor, Color outlineColor, bool visible) :size(size), CollisionArea(position, fillColor, outlineColor, visible) {}

bool BoxCollision::is_overlapping(CollisionArea* other) const
{
	if (auto circleCollision = dynamic_cast<const CircleCollision*>(other))
	{
		FVector min = position - size / 2.f;
		Vector max = position + size / 2.f;

		FVector clamped = FVector(
			std::max(min.x, std::min(circleCollision->get_position().x, max.x)),
			std::max(min.y, std::min(circleCollision->get_position().y, max.y)));

		return (circleCollision->get_position() - clamped).size_squared() <= circleCollision->get_radius() * circleCollision->get_radius();
	}
	else if (auto boxCollision = dynamic_cast<const BoxCollision*>(other))
	{
		return FRect(position - size / 2.f, size).find_intersection(FRect(boxCollision->position - boxCollision->size / 2.f, boxCollision->size)).has_value();
	}
	else return false;
}

bool BoxCollision::contains_point(const FVector& point) const
{
	return FRect(position - size / 2.f, size).contains_point(point);
}

void BoxCollision::render() const
{
	if (!visible) return;

	sf::RectangleShape shape = sf::RectangleShape(size);
	shape.setPosition(position - size / 2.f);
	shape.setFillColor(fillColor);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(outlineColor);

	GAME_WINDOW.render(shape, nullptr);
}

const FVector& BoxCollision::get_size() const 
{
	return size;
}

void BoxCollision::set_size(const FVector& new_size)
{ 
	size = new_size; 
}