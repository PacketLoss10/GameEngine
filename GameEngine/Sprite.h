#pragma once

#include "RenderComponent.h"
#include "TextureLoader.h"

class TextureRect
{
private:
	IVector position = IVector(0, 0);
	IVector size = IVector(1, 1);
public:
	TextureRect() = default;
	TextureRect(IVector position, IVector size) :position(IVector(std::max(0, position.x), std::max(0, position.y))), size(IVector(std::max(1, size.x), std::max(1, size.y))) {}
	operator sf::IntRect() const
	{
		return sf::IntRect(position, size);
	}
};

class Texture
{
public:
	static std::string empty;
	std::string filepath = empty;
	Texture() = default;
	Texture(std::string filepath) :filepath(filepath) {}
};

class NormalMap
{
public:
	static std::string empty;
	std::string filepath = empty;
	NormalMap() = default;
	NormalMap(std::string filepath) :filepath(filepath) {}
};

class Sprite :public RenderComponent
{
private:
	static void generate_normal_map(Sprite& sprite, float value);
protected:
	TextureRect rect = TextureRect();
	Texture texture = Texture();
	NormalMap normal = NormalMap();
public:
	Sprite() = default;

	void init(Entity* owner, bool enabled, Texture texture, TextureRect rect, NormalMap normal);

	const TextureRect& get_rect() const;
	void set_rect(const TextureRect& rect);

	const Texture& get_texture() const;
	void set_texture(const Texture& texture);

	const NormalMap& get_normal() const;
	void set_normal(const NormalMap& normal);
};