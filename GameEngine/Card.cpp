#include "Card.h"
#include "CardZone.h"
#include "World.h"
#include "InputHandler.h"
#include "TickClock.h"

Card::Card(std::string front, std::string back) : front(front), back(back)
{
	sprite = new SpriteComponent(this);
	sprite->set_texture(Texture("Cards//" + front));
	sprite->set_rect(TextureRect(IntVector(0, 0), IntVector(672, 936)));
	sprite->set_relativePosition(Vector2(-336.f, -468.f));

	collision = new BoxCollisionComponent(this);
	collision->set_size(Vector2(672.f, 936.f));

	dragDrop = new DragDropComponent(this);
	dragDrop->set_geometry(collision);
	dragDrop->on_hover_begin.bind(this, &Card::mouse_hover);
	dragDrop->on_hover_end.bind(this, &Card::mouse_unhover);
	dragDrop->on_drag_end.bind(this, &Card::drag_end);

	set_scale(Vector2(0.3f, 0.3f));
}

Card::~Card()
{
	delete sprite;
	delete collision;
	delete dragDrop;
}

void Card::update_tick()
{
	dragDrop->set_layer(sprite->get_zOrder());
}

void Card::input_tick()
{
	if (INPUT.is_button_pressed(Mouse::M2) && dragDrop->is_selected())
	{
		tapped ? untap() : tap();
	}
	if (INPUT.is_button_pressed(Mouse::M3) && dragDrop->is_selected())
	{
		flipped ? unflip() : flip();
	}
}

void Card::tap()
{
	tapped = true;
	set_forward(Vector2(0.f, -1.f));
}

void Card::untap()
{
	tapped = false;
	set_forward(Vector2(1.f, 0.f));
}

void Card::flip()
{
	flipped = true;
	sprite->set_texture(Texture("Cards//" + back));
}

void Card::unflip()
{
	flipped = false;
	sprite->set_texture(Texture("Cards//" + front));
}

void Card::zoom()
{
	zoomed = true;
	set_scale(Vector2(0.8f, 0.8f));
}

void Card::unzoom()
{
	zoomed = false;
	dragDrop->is_selected() ? set_scale(Vector2(0.35f, 0.35f)) : set_scale(Vector2(0.3f, 0.3f));
}

void Card::mouse_hover()
{
	sprite->to_front();
	set_scale(Vector2(0.35f, 0.35f));
}

void Card::mouse_unhover()
{
	zoomed = false;
	set_scale(Vector2(0.3f, 0.3f));
}

void Card::drag_end(const Vector2& mousePos)
{
	for (CardZone* zone : WORLD.all_entities_of_type<CardZone>())
	{
		if (zone->get_area()->is_mouseOverlapping())
		{
			zone->add_card(this);
			despawn();
			break;
		}
	}
}

SpriteComponent* Card::get_sprite() const
{
	return sprite;
}

BoxCollisionComponent* Card::get_collision() const
{
	return collision;
}

DragDropComponent* Card::get_dragDrop() const
{
	return dragDrop;
}