#include "Renderer.h"
#include "Sprite.h"
#include "Light.h"

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

void Renderer::render(const std::vector<Renderable*>& data)
{
    if (data.empty())
        return;

    std::vector<Sprite*> sprites;
    sprites.reserve(data.size());

    constexpr int MAX_LIGHTS = 16;
    std::vector<Light*> lights;
    lights.reserve(std::min(data.size(), static_cast<size_t>(MAX_LIGHTS)));

    // Isolate sprites and lights
    for (Renderable* renderable : data)
    {
        if (Sprite* sprite = dynamic_cast<Sprite*>(renderable))
        {
            sprites.push_back(sprite);
        }
        else if (Light* light = dynamic_cast<Light*>(renderable))
        {
            lights.push_back(light);
        }
    }

    // Light data init
    int lightCount = std::min(static_cast<int>(lights.size()), MAX_LIGHTS);

    std::vector<sf::Glsl::Vec2> positions;
    positions.reserve(lightCount);

    std::vector<float> radii;
    radii.reserve(lightCount);

    std::vector<sf::Glsl::Vec3> colors;
    colors.reserve(lightCount);

    std::vector<float> brightness;
    brightness.reserve(lightCount);

    for (const Light* light : lights)
    {
        const FVector& pos = light->get_transform().position;
        positions.emplace_back(pos.x, 1080.f - pos.y);

        radii.push_back(light->get_radius());

        const Color& c = light->get_color();
        colors.emplace_back(c.r / 255.f, c.g / 255.f, c.b / 255.f);

        brightness.push_back(light->get_brightness());
    }

    // Rendering
    for (const Sprite* sprite : sprites)
    {
        const sf::Texture& texture = TEXTURE_LOADER.load_texture(sprite->get_texture());
        const sf::Texture& normalMap = TEXTURE_LOADER.load_texture(sprite->get_normalMap());

        sf::Sprite s = sf::Sprite(texture, sprite->get_rect());
        s.setPosition(sprite->get_transform().position);
        s.setRotation(sf::radians(sprite->get_transform().forward.angle()));
        s.setScale(sprite->get_transform().scale);

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

        GAME_WINDOW.render(s, &shader);
    }
}

void Renderer::end_render() const
{
	GAME_WINDOW.end_render();
}

sf::Shader* Renderer::get_shader()
{
	return &shader;
}