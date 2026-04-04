#include "CreateSpriteMessage.h"

CreateSpriteMessage::CreateSpriteMessage(int spriteId, std::string filename, TextureRect rect) :spriteId(spriteId), filename(filename), rect(rect) {}

ByteArray CreateSpriteMessage::serialize() const
{
	ByteArray ba;

	ba.put(GameMessageType::CreateSprite);
	ba.put(spriteId);
	ba.put(filename.size());
	ba.put(filename.data(), filename.size());
	ba.put(rect.get_position().x);
	ba.put(rect.get_position().y);
	ba.put(rect.get_position().x);
	ba.put(rect.get_position().y);

	return ba;
}

CreateSpriteMessage* CreateSpriteMessage::deserialize(ByteArray& ba)
{
	int spriteId = ba.get<int>();

	int filenameSize = ba.get<int>();
	std::string filename = ba.get<char>(filenameSize);

	int rectPosX = ba.get<int>();
	int rectPosY = ba.get<int>();
	int rectSizeX = ba.get<int>();
	int rectSizeY = ba.get<int>();
	TextureRect rect(IntVector(rectPosX, rectPosY), IntVector(rectSizeX, rectSizeY));

	return new CreateSpriteMessage(spriteId, filename, rect);
}

void CreateSpriteMessage::execute() {}