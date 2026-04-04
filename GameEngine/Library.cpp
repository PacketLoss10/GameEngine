#include "Library.h"
#include "World.h"
#include "InputHandler.h"
#include <algorithm>
#include <random>

Library::Library()
{
	label->set_text("Library");
}

Library::~Library()
{
	delete sprite;
}

void Library::input_tick()
{
	if (INPUT.is_button_pressed(Mouse::M3) && mouseInteraction->is_selected())
	{
		shuffle();
	}
}

Card* Library::remove_card()
{
	if (cards.empty())
		return nullptr;

	Card* card = cards.back();
	WORLD.spawn_entity(card);
	cards.pop_back();

	if (cards.empty())
		sprite->set_enabled(false);

	return card;
}

void Library::add_card(Card* card)
{
	cards.push_back(card);

	sprite->set_enabled(true);
}

void Library::shuffle()
{
	if (cards.size() <= 1)
		return;

	std::random_device rd;
	std::mt19937 rng(rd());

	std::shuffle(cards.begin(), cards.end(), rng);
}