#pragma once

#include "GameMessage.h"
#include "Vector2.h"

class MoveSpriteMessage :public GameMessage
{
private:
	static inline bool registered = GameMessage::register_deserializer<MoveSpriteMessage>(GameMessageType::MoveSprite);
public:
	MoveSpriteMessage(int spriteId, Vector2 to);

	int spriteId = 0;
	Vector2 to = Vector2();

	ByteArray serialize() const override;
	static MoveSpriteMessage* deserialize(ByteArray& ba);

	void execute() override;
};