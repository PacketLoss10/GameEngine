#pragma once

#include "ByteArray.h"

enum class GameMessageType : uint8_t
{
	Register = 0,
	Text = 1,
	InputTap = 4,
	InputPan = 5,
	CreateSprite = 2,
	MoveSprite = 3,
};

class GameMessage
{
protected:
	using Deserializer = std::function<GameMessage* (ByteArray&)>;
	static std::unordered_map<GameMessageType, Deserializer>& deserializers()
	{
		static std::unordered_map<GameMessageType, Deserializer> map;
		return map;
	}
	template<typename T>
	static bool register_deserializer(GameMessageType type)
	{
		deserializers()[type] = [](ByteArray& ba)->GameMessage* {return T::deserialize(ba);};
		return true;
	}
public:
	GameMessage() = default;
	virtual ~GameMessage() = default;

	virtual ByteArray serialize() const = 0;
	static GameMessage* decode(ByteArray& ba);

	virtual void execute() = 0;
};