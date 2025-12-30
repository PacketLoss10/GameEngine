#include <SFML/Graphics.hpp>
#include <vector>
#include "InputHandler.h"
#include <cmath>

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	sf::Vector2u screenSize = { 800,600 };
	sf::RenderWindow window(sf::VideoMode(screenSize), "Lighting Test");

	// Sprite
	sf::Texture tex{ "sprite.png" };
	sf::Sprite sprite1{ tex };
	sprite1.setScale(sf::Vector2f(5.f, 5.f));

	// Shader
	sf::Shader coreShader;
	if (!coreShader.loadFromFile("shader.frag", sf::Shader::Type::Fragment))
	{
		std::cout << "Could not load core shader" << std::endl;
	}

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		// Draw
		window.clear(sf::Color::Black);

		auto mousePos = sf::Mouse::getPosition(window);
		coreShader.setUniform("u_position", sf::Glsl::Vec2(mousePos.x, screenSize.y - mousePos.y));
		coreShader.setUniform("u_radius", 100.0f);
		coreShader.setUniform("u_texture", sprite1.getTexture());
		window.draw(sprite1, &coreShader);

		window.display();
	}
}