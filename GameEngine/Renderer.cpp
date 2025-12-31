#include "Renderer.h"
#include "Sprite.h"
#include "WorldSystem.h"
#include "LightSource.h"

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
    const sf::Texture& texture = TEXTURE_LOADER.load_texture(data.get_texture());
    const sf::Texture& normalMap = TEXTURE_LOADER.load_texture(data.get_normalMap());

    sf::Sprite sprite = sf::Sprite(texture, data.get_rect());
    sprite.setPosition(transform.position);
    sprite.setRotation(sf::radians(transform.forward.angle()));
    sprite.setScale(transform.scale);

    auto lights = WORLD.find_all_actors_of_type<LightSource>();

    constexpr int MAX_LIGHTS = 16;
    int lightCount = std::min((int)lights.size(), MAX_LIGHTS);

    std::vector<sf::Glsl::Vec2> positions;
    std::vector<float> radii;
    std::vector<sf::Glsl::Vec3> colors;
    std::vector<float> brightness;

    positions.reserve(lightCount);
    radii.reserve(lightCount);
    colors.reserve(lightCount);
    brightness.reserve(lightCount);

    for (int i = 0; i < lightCount; ++i)
    {
        LightSource* light = (LightSource*)lights[i];

        const FVector& pos = light->get_transform().position;

        positions.emplace_back(pos.x, 1080.f - pos.y);
        radii.push_back(light->get_radius());

        const Color& c = light->get_color();
        colors.emplace_back(c.r / 255.f, c.g / 255.f, c.b / 255.f);

        brightness.push_back(light->get_brightness());
    }

    shader.setUniform("u_lightCount", lightCount);

    if (lightCount > 0)
    {
        shader.setUniformArray("u_lightPosition", positions.data(), lightCount);
        shader.setUniformArray("u_lightRadius", radii.data(), lightCount);
        shader.setUniformArray("u_lightColor", colors.data(), lightCount);
        shader.setUniformArray("u_lightBrightness", brightness.data(), lightCount);
    }

    shader.setUniform("u_texture", texture);
    shader.setUniform("u_normalMap", normalMap);

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