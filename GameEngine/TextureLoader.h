#pragma once

#include "Texture.h"
#include "SFML/Graphics.hpp"
#include "iostream"

#define TEXTURE_LOADER TextureLoader::instance()

enum class TextureLoadContext
{
	Texture, NormalMap
};

class TextureLoader 
{
private:
	std::unordered_map<std::string, sf::Texture> textureMap;
	sf::Texture emptyTexture;
	sf::Texture emptyNormal;
	TextureLoader();
	TextureLoader(const TextureLoader&) = delete;
	TextureLoader& operator=(const TextureLoader&) = delete;
public:
	static TextureLoader& instance();
	const sf::Texture& load_texture(const std::string& path, TextureLoadContext context);
};