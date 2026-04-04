#include "CommandZone.h"
#include "World.h"

CommandZone::CommandZone()
{
	label->set_text("Command Zone");
	label->set_characterSize(80);
}

CommandZone::~CommandZone()
{
	delete sprite;
}