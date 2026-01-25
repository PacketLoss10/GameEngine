#pragma once

#include "TextureLoader.h"

#include "NavMesh.h"

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

	NavMesh navmesh;
public:
	static Renderer& instance();
	void push(Light* lightData);
	void push(Sprite* spriteData);
	void render(Window& window);
	sf::Shader* get_shader();

	void set_navmesh(const NavMesh& navmesh);
};