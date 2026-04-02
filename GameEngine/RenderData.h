#pragma once

#include "Texture.h"
#include "NormalMap.h"
#include "TextureRect.h"
#include "Transform.h"
#include "Color.h"

enum class RenderDataType
{
	Sprite,
	Light,
	Text,
	Primitive
};

enum class PrimitiveType
{
	Box,
	Circle
};

struct LightingData
{
	bool lit = false;
	NormalMap normal = NormalMap();
};

struct SpriteRenderData
{
	Texture texture = Texture();
	TextureRect rect = TextureRect();
	LightingData lighting = LightingData();
	int Zorder = 0;

	Transform transform = Transform();

	bool enabled = true;
};

struct LightRenderData
{
	float radius = 0.f;
	float brightness = 0.f;
	Color color = Color();

	Vector2 position = Vector2();

	bool enabled = true;
};

struct PrimitiveRenderData
{
	PrimitiveType type = PrimitiveType::Box;
	Color fillColor = Color(0, 0, 0, 0);
	Color outlineColor = Color(255, 255, 255, 255);
	LightingData lighting = LightingData();
	int zOrder = 0;

	Vector2 boxSize = Vector2();
	Vector2 circleRadius = Vector2();
	Transform transform = Transform();

	bool enabled = true;
};

struct TextRenderData
{
	std::string text = "";
	std::string fontFilepath = "";
	int characterSize = 0;
	Color fillColor = Color();
	Color outlineColor = Color();
	LightingData lighting = LightingData();
	int zOrder = 0;

	Transform transform = Transform();

	bool enabled = true;
};

struct RenderData
{
	RenderDataType type;
	int zOrder = 0;

	union
	{
		SpriteRenderData spriteData;
		PrimitiveRenderData primitiveData;
		TextRenderData textData;
	};

	RenderData(const SpriteRenderData& sprite) : type(RenderDataType::Sprite), zOrder(sprite.Zorder), spriteData(sprite)
	{
		new (&spriteData) SpriteRenderData(sprite);
	}

	RenderData(const PrimitiveRenderData& primitive) : type(RenderDataType::Primitive), zOrder(primitive.zOrder), primitiveData(primitive)
	{
		new (&primitiveData) PrimitiveRenderData(primitive);
	}

	RenderData(const TextRenderData& text) : type(RenderDataType::Text), zOrder(text.zOrder), textData(text)
	{
		new (&textData) TextRenderData(text);
	}

	~RenderData()
	{
		destroy();
	}

	void destroy()
	{
		switch (type)
		{
		case RenderDataType::Sprite: spriteData.~SpriteRenderData(); break;
		case RenderDataType::Primitive: primitiveData.~PrimitiveRenderData(); break;
		case RenderDataType::Text: textData.~TextRenderData(); break;
		}
	}

	RenderData(const RenderData& other) : type(other.type), zOrder(other.zOrder)
	{
		switch (type)
		{
		case RenderDataType::Sprite: new (&spriteData) SpriteRenderData(other.spriteData); break;
		case RenderDataType::Primitive: new (&primitiveData) PrimitiveRenderData(other.primitiveData); break;
		case RenderDataType::Text: new (&textData) TextRenderData(other.textData); break;
		}
	}

	RenderData& operator=(const RenderData& other)
	{
		if (this != &other)
		{
			destroy();
			type = other.type;
			zOrder = other.zOrder;

			switch (type)
			{
			case RenderDataType::Sprite: new (&spriteData) SpriteRenderData(other.spriteData); break;
			case RenderDataType::Primitive: new (&primitiveData) PrimitiveRenderData(other.primitiveData); break;
			case RenderDataType::Text: new (&textData) TextRenderData(other.textData); break;
			}
		}
		return *this;
	}
};