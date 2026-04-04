#include "Exile.h"
#include "World.h"

Exile::Exile()
{
	label->set_text("Exile");
}

Exile::~Exile()
{
	delete sprite;
}