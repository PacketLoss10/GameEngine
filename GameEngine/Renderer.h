#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "RenderData.h"

class Window;

#define RENDERER Renderer::instance()

class Renderer
{
private:
	sf::Shader shader;

	std::vector<RenderData> renderData;
	std::vector<LightRenderData> lightData;

	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
public:
	static Renderer& instance();

	void push(const SpriteRenderData& data);
	void push(const PrimitiveRenderData& data);
	void push(const TextRenderData& data);

	void push(const LightRenderData& data);

	void render(Window& window);
};