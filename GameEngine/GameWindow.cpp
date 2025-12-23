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

void GameWindow::render(const sf::Drawable& renderObject)
{
	window.draw(renderObject);
}

void GameWindow::end_render()
{
	window.display();
}

FVector GameWindow::get_mouse_pos() const
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return FVector(pos.x, pos.y);
}