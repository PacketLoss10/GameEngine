#pragma once

#include "GameMessage.h"
#include "SpriteComponent.h"

class CreateSpriteMessage :public GameMessage
{
private:
	static inline bool registered = GameMessage::register_deserializer<CreateSpriteMessage>(GameMessageType::CreateSprite);
public:
	CreateSpriteMessage(int spriteId, std::string filename, TextureRect rect);

	int spriteId = 0;
	std::string filename = "";
	TextureRect rect = TextureRect();

	ByteArray serialize() const override;
	static CreateSpriteMessage* deserialize(ByteArray& ba);

	void execute() override;
};