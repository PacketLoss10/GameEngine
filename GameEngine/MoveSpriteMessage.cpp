#include "MoveSpriteMessage.h"

MoveSpriteMessage::MoveSpriteMessage(int spriteId, Vector2 to) :GameMessage(), spriteId(spriteId), to(to) {}

ByteArray MoveSpriteMessage::serialize() const
{
	ByteArray ba;

	ba.put(GameMessageType::MoveSprite);
	ba.put(spriteId);
	ba.put(to.x);
	ba.put(to.y);

	return ba;
}

MoveSpriteMessage* MoveSpriteMessage::deserialize(ByteArray& ba)
{
	int spriteId = ba.get<int>();

	float toX = ba.get<float>();
	float toY = ba.get<float>();
	Vector2 to(toX, toY);

	return new MoveSpriteMessage(spriteId, to);
}

void MoveSpriteMessage::execute() {}