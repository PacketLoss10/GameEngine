#include "Library.h"
#include "InputHandler.h"

Library::Library()
{
	sprite = new SpriteComponent(this);
	sprite->set_texture(Texture("back-of-card.png"));
	sprite->set_rect(TextureRect(IntVector(0, 0), IntVector(672, 936)));
	sprite->set_lit(false);
	sprite->set_relativePosition(Vector2(-336.f, -468.f));
	sprite->finalise();

	collision = new BoxCollisionComponent(this);
	collision->set_size(Vector2(672.f, 936.f));
	collision->finalise();

	set_scale(Vector2(0.5f, 0.5f));
}

Library::~Library()
{
	delete sprite;
	delete collision;
}

void Library::input_tick()
{
	if (INPUT.is_button_pressed(Mouse::M1))
	{
		if (collision->is_mouseOverlapping())
		{
			draw_card();
		}
	}

	if (INPUT.is_button_pressed(Mouse::M2))
	{
		if (collision->is_mouseOverlapping())
		{
			shuffle();
		}
	}
}

Card* Library::draw_card()
{
	Card* card = library.back();
	library.pop_back();
	return card;
}

void Library::add_card(Card* card, LibraryPosition at)
{
	switch (at) 
	{
	case LibraryPosition::Top:
		library.push_back(card);
		break;

	case LibraryPosition::Bottom:
		library.push_front(card);
		break;
	}
}

void Library::shuffle()
{
	for (int i = 0; i < 1000; i++)
	{
		size_t p1 = static_cast<size_t>(rand() % library.size());
		size_t p2 = static_cast<size_t>(rand() % library.size());

		library[p1] = library[p2];
	}
}
