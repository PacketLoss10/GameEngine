#include "RegisterMessage.h"

RegisterMessage::RegisterMessage(std::string playerId) :GameMessage(), playerId(playerId) {}

ByteArray RegisterMessage::serialize() const
{
	ByteArray ba;

	ba.put(GameMessageType::Register);
	ba.put(playerId.size());
	ba.put(playerId.data(), playerId.size());

	return ba;
}

RegisterMessage* RegisterMessage::deserialize(ByteArray& ba)
{
	int playerIdSize = ba.get<int>();
	std::string playerId = ba.get<char>(playerIdSize);

	return new RegisterMessage(playerId);
}

void RegisterMessage::execute()
{
	std::cout << "Player: " << playerId << " registered to the server" << std::endl;
}