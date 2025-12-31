#pragma once

#include "EngineUtils.h"
#include "TextureLoader.h"
#include "GameWindow.h"

class Sprite;

struct LightData
{
	FVector position;
	float radius;
	Color color;
	float brightness;
};

struct SpriteData
{
	std::string texture;
	std::string normalMap;
	IRect rect;
	Transform transform;
};

struct RenderData
{
	std::vector<SpriteData> spriteData;
	std::vector<LightData> lightData;
};

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
	void render(const Sprite& data, const Transform& transform);
	void end_render() const;
	sf::Shader* get_shader();
};