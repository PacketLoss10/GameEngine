#pragma once

#include "core.h"
#include "TextureLoader.h"
#include "GameWindow.h"

class RenderObject;

#define RENDERER Renderer::instance()

class Renderer
{
private:
	sf::Shader shader;
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
public:
	static Renderer& instance();
	void start_render() const;
	//void render(const Sprite& data, const Transform& transform);
	void render(const std::vector<RenderObject*>& data);
	void end_render() const;
	sf::Shader* get_shader();
};