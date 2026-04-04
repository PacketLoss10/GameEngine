#include "Hand.h"

Hand::Hand()
{
	area = new BoxCollisionComponent(this);
	area->set_size(Vector2(672.f, 936.f));

	outline = new PrimitiveBoxComponent(this);
	outline->set_size(Vector2(672.f, 936.f));
	outline->set_fillColor(Color(0, 0, 0, 0));
	outline->set_outlineColor(Color(255, 255, 255, 255));
	outline->set_outlineThickness(5.f);
	outline->set_relativePosition(Vector2(-336.f, -468.f));

	label = new TextComponent(this);
	label->set_text("Hand");
	label->set_fontFilepath("font.ttf");
	label->set_characterSize(100);
	label->set_fillColor(Color(255, 255, 255, 255));
	label->set_outlineThickness(0.f);
	label->set_zOrder(-1);
	label->set_relativePosition(Vector2(-0.f, -520.f));
	label->set_autoCenter(true);
}

Hand::~Hand()
{
	delete area;
	delete outline;
	delete label;
}

void Hand::mouse_hover()
{

}

void Hand::mouse_unhover()
{

}

void Hand::drag_begin(const Vector2& mousePos)
{

}

BoxCollisionComponent* Hand::get_area() const
{
	return area;
}

PrimitiveBoxComponent* Hand::get_outline() const
{
	return outline;
}

TextComponent* Hand::get_label() const
{
	return label;
}