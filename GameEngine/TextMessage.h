#pragma once

#include "GameMessage.h"

class TextMessage :public GameMessage
{
private:
	static inline bool registered = GameMessage::register_deserializer<TextMessage>(GameMessageType::Text);
public:
	TextMessage(std::string playerId, std::string text);

	std::string playerId = "";
	std::string text = "";

	ByteArray serialize() const override;
	static TextMessage* deserialize(ByteArray& ba);

	void execute() override;
};