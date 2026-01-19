#pragma once

#include "TextureLoader.h"

class Window;
class Light;
class Sprite;

#define RENDERER Renderer::instance()

class Renderer
{
private:
	sf::Shader shader;
	std::vector<Sprite*> sprites;
	std::vector<Light*> lights;
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
public:
	static Renderer& instance();
	void push(Light* lightData);
	void push(Sprite* spriteData);
	void render(Window& window);
	sf::Shader* get_shader();
};