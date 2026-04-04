#include "SpriteComponent.h"
#include "RenderComponentManager.h"
#include <iostream>
#include <filesystem>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector3.hpp>

void SpriteComponent::generate_normal_map(SpriteComponent& sprite, float value, const std::string& folder, const std::string& name)
{
	if (!std::filesystem::exists(folder))
	{
		std::cerr << "Failed to open folder: " << folder << std::endl;
		return;
	}

	const std::string defaultNormalMapName = "normalmap_" + sprite.texture.filepath;
	std::string normalMapFilepath;
	if (name == "")
		normalMapFilepath = folder + "//" + defaultNormalMapName;
	else 
		normalMapFilepath = folder + "//" + name;

	if (std::filesystem::exists(normalMapFilepath))
	{
		sprite.normal.filepath = normalMapFilepath;
		return;
	}

	sf::Image image;
	if (!image.loadFromFile(sprite.texture.filepath))
	{
		std::cerr << "Failed to load texture for normal map generation: " << sprite.texture.filepath << std::endl;
		return;
	}
	sf::Vector2u size = image.getSize();

	sf::Image normalImage(size, sf::Color::Black);

	auto getBrightness = [&](int x, int y)
		{
			x = std::clamp(x, 0, static_cast<int>(size.x) - 1);
			y = std::clamp(y, 0, static_cast<int>(size.y) - 1);
			sf::Color pixelColor = image.getPixel(sf::Vector2u(x, y));
			return (0.299f * pixelColor.r + 0.587f * pixelColor.g + 0.114f * pixelColor.b) / 255.f;
		};

	for (unsigned int y = 0; y < size.y; y++)
	{
		for (unsigned int x = 0; x < size.x; x++)
		{
			float heightL = getBrightness(x - 1, y);
			float heightR = getBrightness(x + 1, y);
			float heightU = getBrightness(x, y - 1);
			float heightD = getBrightness(x, y + 1);

			float dx = (heightR - heightL) * value;
			float dy = (heightD - heightU) * value;

			sf::Vector3f normal(-dx, -dy, 1.0f);
			float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			normal.x /= length;
			normal.y /= length;
			normal.z /= length;

			std::uint8_t r = static_cast<std::uint8_t>((normal.x * 0.5f + 0.5f) * 255.0f);
			std::uint8_t g = static_cast<std::uint8_t>((normal.y * 0.5f + 0.5f) * 255.0f);
			std::uint8_t b = static_cast<std::uint8_t>((normal.z * 0.5f + 0.5f) * 255.0f);

			normalImage.setPixel(sf::Vector2u(x, y), sf::Color(r, g, b));
		}
	}

	if (!normalImage.saveToFile(normalMapFilepath))
	{
		std::cerr << "Failed to save normal map to " << normalMapFilepath << std::endl;
		return;
	}
	else
	{
		sprite.normal.filepath = normalMapFilepath;
		return;
	}
}

SpriteComponent::SpriteComponent(Entity* owner) :RenderComponent(owner), ZSortable(0) {}

RenderDataType SpriteComponent::get_type() const
{
	return RenderDataType::Sprite;
}

SpriteRenderData SpriteComponent::build_render_data() const
{
	SpriteRenderData data;

	data.texture = texture;
	data.rect = rect;
	data.lighting = LightingData(lit, normal);
	data.Zorder = get_zOrder();
	data.transform = get_worldTransform();
	data.enabled = enabled;

	return data;
}

const Texture& SpriteComponent::get_texture() const
{
	return texture;
}

void SpriteComponent::set_texture(const Texture& texture)
{
	this->texture = texture;
}

const NormalMap& SpriteComponent::get_normal() const
{
	return normal;
}

void SpriteComponent::set_normal(const NormalMap& normal)
{
	this->normal = normal;
}

const TextureRect& SpriteComponent::get_rect() const
{
	return rect;
}

void SpriteComponent::set_rect(const TextureRect& rect)
{
	this->rect = rect;
}

bool SpriteComponent::is_lit() const
{
	return lit;
}

void SpriteComponent::set_lit(bool lit)
{
	this->lit = lit;
}