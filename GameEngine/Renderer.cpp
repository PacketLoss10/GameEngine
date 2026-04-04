#include "Renderer.h"
#include "Window.h"
#include "TextureLoader.h"
#include "ZSortable.h"

Renderer::Renderer()
{
	if (!shader.loadFromFile("Assets//Shaders//CORESHADER.frag", sf::Shader::Type::Fragment))
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

void Renderer::set_activeWindow(Window* activeWindow)
{
	this->activeWindow = activeWindow;
}

void Renderer::push(const SpriteRenderData& data)
{
	if (!data.enabled)
		return;

	renderData.emplace_back(data);
}

void Renderer::push(const PrimitiveRenderData& data)
{
	if (!data.enabled)
		return;

	renderData.emplace_back(data);
}

void Renderer::push(const TextRenderData& data)
{
	if (!data.enabled)
		return;

	renderData.emplace_back(data);
}

void Renderer::push(const LightRenderData& data)
{
	if (!data.enabled)
		return;

	lightData.push_back(data);
}

void Renderer::render()
{
	if (!activeWindow)
		return;

	//if (renderData.empty() && lightData.empty())
	//	return;

	activeWindow->start_display();

	std::sort(renderData.begin(), renderData.end(), [](const RenderData& a, const RenderData& b) { return a.zOrder < b.zOrder; });

	constexpr int MAX_LIGHTS = 16;
	const int numLights = std::min(static_cast<int>(lightData.size()), MAX_LIGHTS);

	std::array<sf::Glsl::Vec2, MAX_LIGHTS> positions;
	std::array<float, MAX_LIGHTS> radii;
	std::array<sf::Glsl::Vec3, MAX_LIGHTS> colors;
	std::array<float, MAX_LIGHTS> brightnesses;

	for (size_t i = 0; i < numLights; ++i)
	{
		const LightRenderData& light = lightData[i];

		const Vector2& pos = light.position;
		positions[i] = sf::Glsl::Vec2(pos.x, activeWindow->get_size().y - pos.y);

		radii[i] = light.radius;

		const Color& c = light.color;
		colors[i] = sf::Glsl::Vec3(c.r / 255.f, c.g / 255.f, c.b / 255.f);

		brightnesses[i] = light.brightness;
	}

	shader.setUniform("u_lightCount", numLights);
	if (numLights > 0)
	{
		shader.setUniformArray("u_lightPosition", positions.data(), numLights);
		shader.setUniformArray("u_lightRadius", radii.data(), numLights);
		shader.setUniformArray("u_lightColor", colors.data(), numLights);
		shader.setUniformArray("u_lightBrightness", brightnesses.data(), numLights);
	}

	for (const RenderData& data : renderData)
	{
		switch (data.type)
		{
		case RenderDataType::Sprite:
		{
			const SpriteRenderData& spriteData = data.spriteData;

			const sf::Texture& texture = TEXTURE_LOADER.load_texture(spriteData.texture.filepath, TextureLoadContext::Texture);
			sf::Sprite sprite(texture, spriteData.rect);

			sprite.setPosition(spriteData.transform.position);
			sprite.setRotation(sf::radians(std::atan2f(spriteData.transform.forward.y, spriteData.transform.forward.x)));
			sprite.setScale(spriteData.transform.scale);

			if (spriteData.lighting.lit)
			{
				const sf::Texture& normal = TEXTURE_LOADER.load_texture(spriteData.lighting.normal.filepath, TextureLoadContext::NormalMap);
				shader.setUniform("u_texture", texture);
				shader.setUniform("u_normalMap", normal);
				activeWindow->display(sprite, &shader);
			}
			else
			{
				activeWindow->display(sprite, nullptr);
			}
			break;
		}
		case RenderDataType::Primitive:
		{
			const PrimitiveRenderData& primitiveData = data.primitiveData;

			switch (primitiveData.type)
			{
			case PrimitiveType::Box:
			{
				sf::RectangleShape box = sf::RectangleShape();

				box.setSize(primitiveData.boxSize);

				box.setPosition(primitiveData.transform.position);
				box.setRotation(sf::radians(std::atan2f(primitiveData.transform.forward.y, primitiveData.transform.forward.x)));
				box.setScale(primitiveData.transform.scale);

				box.setFillColor(primitiveData.fillColor);
				box.setOutlineColor(primitiveData.outlineColor);
				box.setOutlineThickness(primitiveData.outlineThickness);

				if (primitiveData.lighting.lit)
				{
					static sf::Texture dummyTexture;
					static bool loaded = false;
					if (!loaded)
					{
						sf::Image img(sf::Vector2u(1, 1), sf::Color::White);
						if (dummyTexture.loadFromImage(img))
							loaded = true;
					}

					shader.setUniform("u_texture", dummyTexture);
					shader.setUniform("u_normalMap", dummyTexture);
					activeWindow->display(box, &shader);
				}
				else
				{
					activeWindow->display(box, nullptr);
				}

				break;
			}
			case PrimitiveType::Circle:
			{
				sf::CircleShape circle = sf::CircleShape();

				circle.setRadius(1.f);

				circle.setPosition(primitiveData.transform.position);
				circle.setRotation(sf::radians(std::atan2f(primitiveData.transform.forward.y, primitiveData.transform.forward.x)));
				circle.setScale(primitiveData.circleRadius.component_wise_mult(primitiveData.transform.scale));

				circle.setFillColor(primitiveData.fillColor);
				circle.setOutlineColor(primitiveData.outlineColor);
				circle.setOutlineThickness(primitiveData.outlineThickness);

				if (primitiveData.lighting.lit)
				{
					static sf::Texture dummyTexture;
					static bool loaded = false;
					if (!loaded)
					{
						sf::Image img(sf::Vector2u(1, 1), sf::Color::White);
						if (dummyTexture.loadFromImage(img))
							loaded = true;
					}

					shader.setUniform("u_texture", dummyTexture);
					shader.setUniform("u_normalMap", dummyTexture);
					activeWindow->display(circle, &shader);
				}
				else
				{
					activeWindow->display(circle, nullptr);
				}

				break;
			}
			default:
				break;
			}
			break;
		}
		case RenderDataType::Text:
		{
			const TextRenderData& textData = data.textData;

			sf::Font font;
			if (!font.openFromFile(textData.fontFilepath))
			{
				std::cerr << "Could not load font: " << textData.fontFilepath << std::endl;
				break;
			}

			sf::Text text(font, textData.text, textData.characterSize);

			if (textData.autoCenter)
				text.setOrigin(text.getLocalBounds().position + text.getLocalBounds().size / 2.f);
			text.setPosition(textData.transform.position);
			text.setRotation(sf::radians(std::atan2f(textData.transform.forward.y, textData.transform.forward.x)));
			text.setScale(textData.transform.scale);

			text.setFillColor(textData.fillColor);
			text.setOutlineColor(textData.outlineColor);
			text.setOutlineThickness(textData.outlineThickness);

			if (textData.lighting.lit)
			{
				static sf::Texture dummyTexture;
				static bool loaded = false;
				if (!loaded)
				{
					sf::Image img(sf::Vector2u(1, 1), sf::Color::White);
					if (dummyTexture.loadFromImage(img))
						loaded = true;
				}
				shader.setUniform("u_texture", dummyTexture);
				shader.setUniform("u_normalMap", dummyTexture);
				activeWindow->display(text, &shader);
			}
			else
			{
				activeWindow->display(text, nullptr);
			}
			break;
		}
		}

	}

	renderData.clear();
	lightData.clear();
	activeWindow->end_display();
}