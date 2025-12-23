#include "TextureLoader.h"

TextureLoader::TextureLoader() 
{
	if (!nulltexture.loadFromFile("NULLTEXTURE.png"))
		std::cerr << "ERROR: failed to load nulltexture for TextureLoader" << std::endl;
}

TextureLoader& TextureLoader::instance() 
{
	static TextureLoader instance;
	return instance;
}

const sf::Texture& TextureLoader::load_texture(const std::string& path) 
{
	if (auto it = textureMap.find(path); it != textureMap.end())
		return it->second;
	else
		if (sf::Texture texture; !texture.loadFromFile(path)) 
		{
			std::cerr << "ERROR: failed to load texture at " << path << std::endl;
			return nulltexture;
		}
		else 
		{
			auto it = textureMap.emplace(path, std::move(texture)).first;
			return it->second;
		}
}