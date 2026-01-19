#pragma once

#include "SFML/Graphics.hpp"
#include "Transform.h"

class Window
{
private:
	sf::RenderWindow window;
	IVector size = IVector(800, 450);
	std::string title = "";
public:
	Window(IVector size, std::string title);

	void update();
	void start_display();
	void display(const sf::Drawable& object, sf::Shader* shader);
	void end_display();

	const IVector& get_size() const;
	void set_size(const IVector& size);

	const std::string& get_title() const;
	void set_title(const std::string& title);

	FVector get_mouse_pos() const;

	bool is_open() const;
};