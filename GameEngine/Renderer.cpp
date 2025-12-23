#include "Renderer.h"

Renderer& Renderer::instance() 
{
	static Renderer instance;
	return instance;
}

void Renderer::start_render() const
{
	GAME_WINDOW.start_render();
}

void Renderer::render(const FrameData& data, const Transform& transform) 
{
	sf::Sprite object = sf::Sprite(TextureLoader::instance().load_texture(data.path), data.rect);
	object.setPosition(transform.position);
	object.setRotation(sf::radians(transform.forward.angle()));
	object.setScale(transform.scale);
	GAME_WINDOW.render(object);
}

void Renderer::end_render() const
{
	GAME_WINDOW.end_render();
}