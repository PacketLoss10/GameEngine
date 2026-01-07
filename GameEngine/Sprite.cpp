#include "Sprite.h"

void Sprite::generate_normalMap(float value)
{
	const std::string normalMapFilePath = "normalmap_" + texture;
	if (std::filesystem::exists(normalMapFilePath))
		normalMap = normalMapFilePath;

	sf::Image image;
	if (!image.loadFromFile(texture))
	{
		std::cerr << "Failed to load texture for normal map generation: " << texture << std::endl;
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
		normalMap = normalMapFilePath;
	}
}

Sprite::Sprite()
	:RenderObject(Transform()),
	texture("NULLTEXTURE.png"),
	rect(IRect(IVector(0, 0), IVector(420, 420))),
	normalMap("NULLNORMAL.png") 
{
}

Sprite::Sprite(std::string texture, IRect rect, std::string normalMap)
	:RenderObject(Transform()),
	texture(texture),
	rect(IRect(IVector(std::max(0, rect.position.x), std::max(0, rect.position.y)), IVector(std::max(1, rect.size.x), std::max(1, rect.size.y)))),
	normalMap(normalMap)
{
}

Sprite::Sprite(std::string texture, std::string normalMap)
	:RenderObject(Transform()),
	texture(texture),
	rect(IRect(IVector(0, 0), IVector(1, 1))),
	normalMap(normalMap)
{
	auto textureSize = TEXTURE_LOADER.load_texture(texture).getSize();
	rect = IRect(IVector(0, 0), IVector(textureSize.x, textureSize.y));
}

Sprite::Sprite(std::string texture, IRect rect)
	:RenderObject(Transform()),
	texture(texture),
	rect(IRect(IVector(std::max(0, rect.position.x), std::max(0, rect.position.y)), IVector(std::max(1, rect.size.x), std::max(1, rect.size.y)))),
	normalMap("NULLNORMAL.png")
{
	generate_normalMap(1.f);
}

Sprite::Sprite(std::string texture)
	:RenderObject(Transform()),
	texture(texture),
	rect(IRect(IVector(0, 0), IVector(1, 1))),
	normalMap("NULLNORMAL.png")
{
	auto textureSize = TEXTURE_LOADER.load_texture(texture).getSize();
	rect = IRect(IVector(0, 0), IVector(textureSize.x, textureSize.y));

	generate_normalMap(1.f);
}

const std::string& Sprite::get_texture() const
{
	return texture;
}

const IRect& Sprite::get_rect() const
{
	return rect;
}

const std::string& Sprite::get_normalMap() const
{
	return normalMap;
}