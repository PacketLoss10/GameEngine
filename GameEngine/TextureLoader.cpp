#include "TextureLoader.h"
#include "NormalMap.h"

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
	auto it = textureMap.find(path);
	if (it != textureMap.end())
		return it->second;

	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		std::cerr << "Failed to load texture: " << path << std::endl;
		switch (context)
		{
		case TextureLoadContext::Texture: return emptyTexture;
		case TextureLoadContext::NormalMap: return emptyNormal;
		default: return emptyTexture;
		}
	}

	auto inserted = textureMap.emplace(path, std::move(texture));
	return inserted.first->second;
}