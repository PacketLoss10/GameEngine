#include "GameWindow.h"

GameWindow& GameWindow::instance()
{
	static GameWindow instance;
	return instance;
}

void GameWindow::start_render()
{
	window.clear(sf::Color::Black);
}

void GameWindow::render(const sf::Drawable& renderObject, sf::Shader* shader)
{
	if (shader)
		window.draw(renderObject, shader);
	else
		window.draw(renderObject);
}

void GameWindow::end_render()
{
	window.display();
}

Vector2 GameWindow::get_mouse_pos() const
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return Vector2(pos.x, pos.y);
}

bool GameWindow::is_open() const
{
	return window.isOpen();
}

void GameWindow::update()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
	}
}