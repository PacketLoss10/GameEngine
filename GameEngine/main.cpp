#include "InputHandler.h"
#include "CollisionComponentManager.h"
#include "EntityA.h"
#include "EntityB.h"
#include "TickClock.h"

#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
	EntityA a;
	EntityB b;

	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "");

	while (window.isOpen())
	{
		INPUT.update();

		if (INPUT.is_key_held(Keyboard::W))
			a.get_collision()->move_by(FVector(0.f, -100.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::A))
			a.get_collision()->move_by(FVector(-100.f, 0.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::S))
			a.get_collision()->move_by(FVector(0.f, 100.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::D))
			a.get_collision()->move_by(FVector(100.f, 0.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::Q))
			a.get_collision()->rotate_by(3.14f * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::E))
			a.get_collision()->rotate_by(-3.14f * DELTA_TIME);

		if (INPUT.is_key_held(Keyboard::Up))
			b.get_collision()->move_by(FVector(0.f, -100.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::Left))
			b.get_collision()->move_by(FVector(-100.f, 0.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::Down))
			b.get_collision()->move_by(FVector(0.f, 100.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::Right))
			b.get_collision()->move_by(FVector(100.f, 0.f) * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::K))
			b.get_collision()->rotate_by(3.14f * DELTA_TIME);
		if (INPUT.is_key_held(Keyboard::L))
			b.get_collision()->rotate_by(-3.14f * DELTA_TIME);

		system("cls");
		COLLISION_COMPONENT_MANAGER.update();

		window.clear(sf::Color::White);

		sf::RectangleShape box;
		sf::CircleShape circle;
		sf::Vector2f position;
		sf::Vector2f scale;
		sf::Vector2f forward;

		//box.setFillColor(sf::Color::Blue);
		//box.setSize(a.get_collision()->get_size());
		//box.setOrigin(a.get_collision()->get_size() / 2.f);
		//position = a.get_collision()->get_position();
		//scale = a.get_collision()->get_scale();
		//forward = a.get_collision()->get_forward();
		//box.setPosition(position);
		//box.setScale(scale);
		//box.setRotation(forward.angle());
		//window.draw(box);

		circle.setFillColor(sf::Color::Red);
		circle.setOutlineThickness(0.02f);
		circle.setOutlineColor(sf::Color::Black);
		circle.setRadius(1.f);
		circle.setOrigin(FVector(1.f, 1.f));
		position = a.get_collision()->get_position();
		scale = a.get_collision()->get_scale();
		forward = a.get_collision()->get_forward();
		circle.setPosition(position);
		circle.setScale(scale.componentWiseMul(a.get_collision()->get_radius()));
		circle.setRotation(forward.angle());
		window.draw(circle);

		circle.setFillColor(sf::Color::Blue);
		circle.setOutlineThickness(0.02f);
		circle.setOutlineColor(sf::Color::Black);
		circle.setRadius(1.f);
		circle.setOrigin(FVector(1.f, 1.f));
		position = b.get_collision()->get_position();
		scale = b.get_collision()->get_scale();
		forward = b.get_collision()->get_forward();
		circle.setPosition(position);
		circle.setScale(scale.componentWiseMul(b.get_collision()->get_radius()));
		circle.setRotation(forward.angle());
		window.draw(circle);

		window.display();

		UPDATE_DELTA_TIME;
	}

	return 0;
}