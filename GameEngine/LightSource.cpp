#include "LightSource.h"
#include "Renderer.h"

void LightSource::update()
{
	RENDERER.get_shader()->setUniform("u_lightPosition", sf::Glsl::Vec2(transform.position.x, 1080.f - transform.position.y));
	RENDERER.get_shader()->setUniform("u_lightRadius", radius);
	RENDERER.get_shader()->setUniform("u_lightColor", sf::Glsl::Vec3(color.r, color.g, color.b));
	RENDERER.get_shader()->setUniform("u_lightBrightness", brightness);
}
