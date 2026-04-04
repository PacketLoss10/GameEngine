#include "TextMessage.h"

TextMessage::TextMessage(std::string playerId, std::string text) :GameMessage(), playerId(playerId), text(text) {}

ByteArray TextMessage::serialize() const
{
	ByteArray ba;

	ba.put(GameMessageType::Text);
	ba.put(playerId.size());
	ba.put(playerId.data(), playerId.size());
	ba.put(text.size());
	ba.put(text.data(), text.size());

	return ba;
}

TextMessage* TextMessage::deserialize(ByteArray& ba)
{
	int playerIdSize = ba.get<int>();
	std::string playerId = ba.get<char>(playerIdSize);

	int textSize = ba.get<int>();
	std::string text = ba.get<char>(textSize);

	return new TextMessage(playerId, text);
}


void TextMessage::execute()
{
	std::cout << playerId << ": " << text << std::endl;
}