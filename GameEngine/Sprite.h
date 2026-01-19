#pragma once

#include "RenderComponent.h"
#include "TextureRect.h"
#include "Texture.h"
#include "NormalMap.h"

class Sprite :public RenderComponent, public ZSortable
{
private:
	static void generate_normal_map(Sprite& sprite, float value);
protected:
	TextureRect rect = TextureRect();
	Texture texture = Texture();
	NormalMap normal = NormalMap();
public:
	Sprite() = default;
	Sprite(Entity* owner, bool enabled, Texture texture, TextureRect rect, int zOrder, Transform transform);
	Sprite(Entity* owner, bool enabled, Texture texture, TextureRect rect, NormalMap normal, int zOrder, Transform transform);

	void init() override;

	const TextureRect& get_rect() const;
	void set_rect(const TextureRect& rect);

	const Texture& get_texture() const;
	void set_texture(const Texture& texture);

	const NormalMap& get_normal() const;
	void set_normal(const NormalMap& normal);
};