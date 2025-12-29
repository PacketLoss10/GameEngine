#include "CollisionArea.h"
#include "Actor.h"

CollisionArea::CollisionArea() {}

CollisionArea::CollisionArea(FVector position, Color fillColor, Color outlineColor, bool visible) :position(position), fillColor(fillColor), outlineColor(outlineColor), visible(visible) {}

const FVector& CollisionArea::get_position() const
{
	return position;
}

void CollisionArea::set_position(const FVector& new_position)
{
	position = new_position;
}

const Color& CollisionArea::get_fillColor() const
{
	return fillColor;
}

void CollisionArea::set_fillColor(const Color& new_fillColor)
{
	fillColor = new_fillColor;
}

const Color& CollisionArea::get_outlineColor() const
{
	return outlineColor;
}

void CollisionArea::set_outlineColor(const Color& new_outlineColor)
{
	outlineColor = new_outlineColor;
}

bool CollisionArea::is_visible() const
{
	return visible;
}

void CollisionArea::set_visible(bool new_visible)
{
	visible = new_visible;
}