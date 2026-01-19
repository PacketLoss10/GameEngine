#include "TextureLoader.h"
#include "Sprite.h"

TextureLoader::TextureLoader()
{
	if (!emptyTexture.loadFromFile(Texture::empty))
	{
		std::cerr << "Failed to load " << Texture::empty << std::endl;
		return;
	}
	if (!emptyNormal.loadFromFile(NormalMap::empty))
	{
		std::cerr << "Failed to load " << NormalMap::empty << std::endl;
		return;
	}
}

TextureLoader& TextureLoader::instance()
{
	static TextureLoader instance;
	return instance;
}

const sf::Texture& TextureLoader::load_texture(const std::string& path, TextureLoadContext context)
{
	if (auto it = textureMap.find(path); it != textureMap.end())
		return it->second;

	if (sf::Texture texture; !texture.loadFromFile(path))
	{
		std::cerr << "Failed to load " << path << std::endl;
		switch (context)
		{
		case TextureLoadContext::Texture:
			return emptyTexture;
			break;
		case TextureLoadContext::NormalMap:
			return emptyNormal;
			break;
		default:
			return emptyTexture;
			break;
		}
	}
	else
	{
		auto it = textureMap.emplace(path, std::move(texture)).first;
		return it->second;
	}
}