#include "Card.h"
#include "InputHandler.h"
#include "TickClock.h"

Card::Card()
{
	sprite = new Sprite(this);
	sprite->set_texture(Texture("ugin-eye-of-the-storms.png"));
	sprite->set_texture(Texture("back-of-card.png"));
	sprite->set_rect(TextureRect(IVector(0, 0), IVector(672, 936)));
	sprite->set_lit(false);
	sprite->set_relativePosition(Vector2(-336.f, -468.f));
	sprite->finalise();

	collision = new BoxCollisionComponent(this);
	collision->set_size(Vector2(672.f, 936.f));
	collision->finalise();

	dragDrop = new DragDropComponent(this);
	dragDrop->set_geometry(collision);
	dragDrop->on_hover_begin.bind(this, &Card::bring_to_front);
	dragDrop->finalise();

	set_scale(Vector2(0.25f, 0.25f));
}

Card::~Card()
{
	delete sprite;
	delete collision;
}

void Card::update_tick()
{
	dragDrop->set_layer(sprite->get_zOrder());
}

void Card::input_tick()
{
	if (INPUT.is_button_pressed(Mouse::M2)&&collision->is_mouseOverlapping())
	{
		tapped ? untap() : tap();
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

void Card::bring_to_front(const Vector2&)
{
	sprite->to_front();
}