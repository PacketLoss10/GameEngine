#include "Graveyard.h"
#include "World.h"

Graveyard::Graveyard()
{
	label->set_text("Graveyard");
}

Graveyard::~Graveyard()
{
	delete sprite;
}