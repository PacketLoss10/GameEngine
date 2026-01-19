#pragma once

#include "Transform.h"

class InputHandler;
class Renderer;
class CircleCollisionComponent;
class BoxCollisionComponent;
class SimulationChunk;

#define GAME_WINDOW GameWindow::instance()

class GameWindow
{
private:
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(1920, 1080)), "");
	GameWindow() = default;
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	FVector get_mouse_pos() const;
	void start_render();
	void render(const sf::Drawable& renderObject, sf::Shader* shader);
	void end_render();
	friend class InputHandler;
	friend class Renderer;
	friend class CircleCollisionComponent;
	friend class BoxCollisionComponent;
	friend class SimulationChunk;
public:
	static GameWindow& instance();
	bool is_open() const;
	void update();
};