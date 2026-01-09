#pragma once

#include "core.h"
#include "RenderObject.h"
#include "TextureLoader.h"

class Sprite :public RenderObject
{
private:
	std::string texture;
	std::string normalMap;
	void generate_normalMap(float value = 1.f);
protected:
	IRect rect;
public:
	// Default constructor. Creates a sprite with missing texture and flat normal map.
	Sprite();
	// Constructor with texture and pre-generated normal map.
	Sprite(std::string texture, IRect rect, std::string normalMap);
	// Constructor with texture and pre-generated normal map. Automatically resizes rect.
	Sprite(std::string texture, std::string normalMap);
	// Constructor with texture only. Automatically generates normal map.
	Sprite(std::string texture, IRect rect);
	// Constructor with texture only. Automatically generated normal map. Automatically resizes rect.
	Sprite(std::string texture);
	const std::string& get_texture() const;
	const IRect& get_rect() const;
	const std::string& get_normalMap() const;
};