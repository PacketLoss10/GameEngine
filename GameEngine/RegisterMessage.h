#pragma once

#include "GameMessage.h"

class RegisterMessage :public GameMessage
{
private:
	static inline bool registered = GameMessage::register_deserializer<RegisterMessage>(GameMessageType::Register);
public:
	RegisterMessage(std::string playerId);

	std::string playerId = "";

	ByteArray serialize() const override;
	static RegisterMessage* deserialize(ByteArray& ba);

	void execute() override;
};