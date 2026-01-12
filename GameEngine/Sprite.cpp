#include "Sprite.h"
#include "RenderComponentManager.h"

std::string Texture::empty = "NULLTEXTURE.png";

std::string NormalMap::empty = "NULLNORMAL.png";

void Sprite::generate_normal_map(Sprite& sprite, float value)
{
	const std::string normalMapFilePath = "normalmap_" + sprite.texture.filepath;
	if (std::filesystem::exists(normalMapFilePath))
		sprite.normal.filepath = normalMapFilePath;

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

	if (!normalImage.saveToFile(normalMapFilePath))
	{
		std::cerr << "Failed to save normal map to " << normalMapFilePath << std::endl;
	}
	else
	{
		sprite.normal.filepath = normalMapFilePath;
	}
}

void Sprite::init(Entity* owner, bool enabled, Texture texture, TextureRect rect, NormalMap normal)
{
	this->owner = owner;
	this->enabled = enabled;
	this->texture = texture;
	this->rect = rect;
	this->normal = normal;
	RENDER_COMPONENT_MANAGER.register_component(this);
}

const TextureRect& Sprite::get_rect() const
{
	return rect;
}

void Sprite::set_rect(const TextureRect& rect)
{
	this->rect = rect;
}

const Texture& Sprite::get_texture() const
{
	return texture;
}

void Sprite::set_texture(const Texture& texture)
{
	this->texture = texture;
}

const NormalMap& Sprite::get_normal() const
{
	return normal;
}

void Sprite::set_normal(const NormalMap& normal)
{
	this->normal = normal;
}