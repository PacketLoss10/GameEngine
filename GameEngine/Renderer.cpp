#include "Renderer.h"
#include "Sprite.h"

Renderer::Renderer()
{
	if (!shader.loadFromFile("shader.frag", sf::Shader::Type::Fragment))
	{
		std::cerr << "Failed to load core shader" << std::endl;
		return;
	}
}

Renderer& Renderer::instance() 
{
	static Renderer instance;
	return instance;
}

void Renderer::start_render() const
{
	GAME_WINDOW.start_render();
}

void Renderer::render(const Sprite& data, const Transform& transform) 
{
	sf::Sprite sprite = sf::Sprite(TEXTURE_LOADER.load_texture(data.get_texture()), data.get_rect());
	sprite.setPosition(transform.position);
	sprite.setRotation(sf::radians(transform.forward.angle()));
	sprite.setScale(transform.scale);
	GAME_WINDOW.render(sprite, &shader);
}

void Renderer::end_render() const
{
	GAME_WINDOW.end_render();
}

sf::Shader* Renderer::get_shader()
{
	return &shader;
}