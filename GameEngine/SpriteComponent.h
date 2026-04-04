#pragma once

#include "RenderComponent.h"
#include "ZSortable.h"

class SpriteComponent :public RenderComponent, public ZSortable
{
private:
	Texture texture = Texture();
	NormalMap normal = NormalMap();
	TextureRect rect = TextureRect();
	bool lit = false;
public:
	SpriteComponent(Entity* owner);
	virtual ~SpriteComponent() = default;

	static void generate_normal_map(SpriteComponent& sprite, float value, const std::string& folder, const std::string& name = "");

	RenderDataType get_type() const override;
	SpriteRenderData build_render_data() const;

	const Texture& get_texture() const;
	void set_texture(const Texture& texture);

	const NormalMap& get_normal() const;
	void set_normal(const NormalMap& normal);

	const TextureRect& get_rect() const;
	void set_rect(const TextureRect& rect);

	bool is_lit() const;
	void set_lit(bool lit);
};