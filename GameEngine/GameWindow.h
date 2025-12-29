#pragma once

#include "EngineUtils.h"

class InputHandler;
class Renderer;
class BoxCollision;
class CircleCollision;
class SimulationChunk;

#define GAME_WINDOW GameWindow::instance()

class GameWindow
{
private:
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(1920, 1080)), "");
	GameWindow() = default;
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	static GameWindow& instance();
	FVector get_mouse_pos() const;
	void start_render();
	void render(const sf::Drawable& renderObject);
	void end_render();
	friend class InputHandler;
	friend class Renderer;
	friend class BoxCollision;
	friend class CircleCollision;
	friend class SimulationChunk;
};