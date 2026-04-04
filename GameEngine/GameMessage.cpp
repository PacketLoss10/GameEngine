#include "GameMessage.h"
#include "RegisterMessage.h"
#include "TextMessage.h"

GameMessage* GameMessage::decode(ByteArray& ba)
{
	ba.reset_read();

	GameMessageType type = ba.get<GameMessageType>();
	
	if (auto it = deserializers().find(type); it != deserializers().end())
		return it->second(ba);

	std::cerr << "Unkown GameMessageType" << std::endl;
	return nullptr;
}