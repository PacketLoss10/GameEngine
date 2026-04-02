#include "Renderer.h"
#include "Window.h"
#include "Sprite.h"
#include "Light.h"

Renderer::Renderer()
{
	if (!shader.loadFromFile("CORESHADER.frag", sf::Shader::Type::Fragment))
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

void Renderer::push(Light* lightData)
{
    lights.push_back(lightData);
}

void Renderer::push(Sprite* spriteData)
{
    sprites.push_back(spriteData);
}

void Renderer::render(Window& window)
{
    if (sprites.empty() && lights.empty())
        return;

    window.start_display();

    std::sort(sprites.begin(), sprites.end(), [](const Sprite* a, const Sprite* b) {return a->get_zOrder() > b->get_zOrder(); });

    constexpr int MAX_LIGHTS = 16;
    const int numLights = std::min(static_cast<int>(lights.size()), MAX_LIGHTS);
    std::vector<sf::Glsl::Vec2> positions;
    positions.reserve(numLights);
    std::vector<float> radii;
    radii.reserve(numLights);
    std::vector<sf::Glsl::Vec3> colors;
    colors.reserve(numLights);
    std::vector<float> brightnesses;
    brightnesses.reserve(numLights);
    while (!lights.empty())
    {
        const Light* light = lights.back();

        const Vector2& pos = light->get_worldPosition();
        positions.emplace_back(pos.x, window.get_size().y - pos.y);

        radii.push_back(light->get_radius());

        const Color& c = light->get_color();
        colors.emplace_back(c.r / 255.f, c.g / 255.f, c.b / 255.f);

        brightnesses.push_back(light->get_brightness());

        lights.pop_back();
    }

    while (!sprites.empty())
    {
        const Sprite* sprite = sprites.back();

        const sf::Texture& texture = TEXTURE_LOADER.load_texture(sprite->get_texture().filepath, TextureLoadContext::Texture);

        sf::Sprite s = sf::Sprite(texture, sprite->get_rect());
        s.setPosition(sprite->get_worldPosition());
        s.setRotation(sf::radians(sprite->get_worldRotation()));
        s.setScale(sprite->get_worldScale());

        if (sprite->is_lit())
        {
            const sf::Texture& normal = TEXTURE_LOADER.load_texture(sprite->get_normal().filepath, TextureLoadContext::NormalMap);

            shader.setUniform("u_lightCount", numLights);
            if (numLights > 0)
            {
                shader.setUniformArray("u_lightPosition", positions.data(), numLights);
                shader.setUniformArray("u_lightRadius", radii.data(), numLights);
                shader.setUniformArray("u_lightColor", colors.data(), numLights);
                shader.setUniformArray("u_lightBrightness", brightnesses.data(), numLights);
            }

            shader.setUniform("u_texture", texture);
            shader.setUniform("u_normalMap", normal);

            window.display(s, &shader);
        }
        else
        {
            window.display(s, nullptr);
        }

        sprites.pop_back();
    }

    window.end_display();
}

sf::Shader* Renderer::get_shader()
{
	return &shader;
}