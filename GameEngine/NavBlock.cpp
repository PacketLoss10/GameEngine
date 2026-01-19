#include "NavBlock.h"

NavBlock::NavBlock(sf::Vector2f _size, sf::Vector2f _position) :BoxCollision(_size, sf::Vector2f(0.f,0.f), sf::Color{ 255,0,0,100 }) 
{
	position = _position;
}
