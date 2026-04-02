#include "Card.h"
#include "InputHandler.h"
#include "TickClock.h"

Card::Card(std::string id) : id(id)
{
	sprite = new SpriteComponent(this);
	sprite->set_texture(Texture("Cards//" + id + ".png"));
	sprite->set_rect(TextureRect(IntVector(0, 0), IntVector(672, 936)));
	sprite->set_relativePosition(Vector2(-336.f, -468.f));
	sprite->set_lit(false);
	sprite->finalise();

	collision = new BoxCollisionComponent(this);
	collision->set_size(Vector2(672.f, 936.f));
	collision->finalise();

	dragDrop = new DragDropComponent(this);
	dragDrop->set_geometry(collision);
	dragDrop->on_hover_begin.bind(this, &Card::mouse_hover);
	dragDrop->on_hover_end.bind(this, &Card::mouse_unhover);
	dragDrop->finalise();

	set_scale(Vector2(0.5f, 0.5f));
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
	if (INPUT.is_button_pressed(Mouse::M2) && collision->is_mouseOverlapping())
	{
		tapped ? untap() : tap();
	}
	if (INPUT.is_button_pressed(Mouse::M3) && collision->is_mouseOverlapping())
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
	sprite->set_texture(Texture("Cards//back-of-card.png"));
}

void Card::unflip()
{
	flipped = false;
	sprite->set_texture(Texture("Cards//" + id + ".png"));
}

void Card::mouse_hover(const Vector2&)
{
	sprite->to_front();
	set_scale(Vector2(0.6f, 0.6f));
}

void Card::mouse_unhover(const Vector2&)
{
	set_scale(Vector2(0.5f, 0.5f));
}