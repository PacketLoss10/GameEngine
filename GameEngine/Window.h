#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "IntVector.h"
#include "Vector2.h"

class Window
{
private:
	sf::RenderWindow window;
	IntVector size = IntVector(800, 450);
	std::string title = "";
public:
	Window(IntVector size, std::string title);

	void update();
	void start_display();
	void display(const sf::Drawable& object, sf::Shader* shader);
	void display(sf::Vertex* vertex, size_t count, sf::PrimitiveType type, sf::Shader* shader);
	void end_display();

	const IntVector& get_size() const;
	void set_size(const IntVector& size);

	const std::string& get_title() const;
	void set_title(const std::string& title);

	Vector2 get_mouse_pos() const;

	bool is_open() const;
};