#include "CollisionComponentManager.h"
#include "EntityA.h"
#include "EntityB.h"

#include <SFML/Graphics.hpp>
#include <cmath>

float forwardToAngle(sf::Vector2f forward)
{
    return std::atan2(forward.y, forward.x) * 180.f / 3.14159265f;
}

int main()
{
    EntityA a;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "");

    sf::CircleShape ellipseShape(1.f);
    ellipseShape.setOrigin(sf::Vector2f(0.5f,0.5f));
    ellipseShape.setFillColor(sf::Color::Green);

    sf::Vector2f position(a.get_collision()->get_position());
    sf::Vector2f radii(a.get_collision()->get_radius());
    sf::Vector2f forward(a.get_collision()->get_forward());
    float length = std::sqrt(forward.x * forward.x + forward.y * forward.y);
    forward /= length;

    ellipseShape.setPosition(position);
    ellipseShape.setScale(sf::Vector2f(radii.x, radii.y));
    ellipseShape.setRotation(sf::radians(forwardToAngle(forward)));

    while (window.isOpen())
    {




        window.clear(sf::Color::Black);
        window.draw(ellipseShape);
        window.display();
    }

    return 0;
}