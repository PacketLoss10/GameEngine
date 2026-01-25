#include "Window.h"

Window::Window(IVector size, std::string title) :title(title)
{
	this->size = IVector(std::max(1, std::abs(size.x)), std::max(1, std::abs(size.y)));
	auto windowSize = sf::Vector2u(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
	window = sf::RenderWindow(sf::VideoMode(windowSize), title);
	window.setMaximumSize(windowSize);
	window.setMinimumSize(windowSize);
}

void Window::update()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
	}
}

void Window::start_display()
{
	window.clear(sf::Color::Black);
}

void Window::display(const sf::Drawable& object, sf::Shader* shader)
{
	window.draw(object, shader);
}

void Window::display(sf::Vertex* vertex, size_t count, sf::PrimitiveType type, sf::Shader* shader)
{
	window.draw(vertex, count, type, shader);
}

void Window::end_display()
{
	window.display();
}

const IVector& Window::get_size() const
{
	return size;
}

void Window::set_size(const IVector& size)
{
	this->size = IVector(std::max(1, std::abs(size.x)), std::max(1, std::abs(size.y)));
	auto windowSize = sf::Vector2u(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
	window.setMaximumSize(std::nullopt);
	window.setMinimumSize(std::nullopt);
	window.setSize(windowSize);
	window.setMaximumSize(windowSize);
	window.setMinimumSize(windowSize);
}

const std::string& Window::get_title() const
{
	return title;
}

void Window::set_title(const std::string& title)
{
	this->title = title;
	window.setTitle(title);
}

FVector Window::get_mouse_pos() const
{
	auto mousePos = sf::Mouse::getPosition(window);
	return FVector(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool Window::is_open() const
{
	return window.isOpen();
}