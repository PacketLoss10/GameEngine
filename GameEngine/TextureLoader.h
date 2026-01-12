#pragma once

#include "SFML/Graphics.hpp"
#include "iostream"

#define TEXTURE_LOADER TextureLoader::instance()

class TextureLoader 
{
private:
	std::unordered_map<std::string, sf::Texture> textureMap;
	sf::Texture nulltexture;
	TextureLoader();
	TextureLoader(const TextureLoader&) = delete;
	TextureLoader& operator=(const TextureLoader&) = delete;
public:
	static TextureLoader& instance();
	const sf::Texture& load_texture(const std::string& path);
};