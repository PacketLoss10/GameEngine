#include "TickClock.h"

TickClock& TickClock::instance() 
{
	static TickClock instance;
	return instance;
}

void TickClock::update() 
{ 
	elapsed = clock.restart().asSeconds();
    if (elapsed < 1.f / maxFPS) 
    {
        sf::sleep(sf::seconds(1.f / maxFPS - elapsed));
        elapsed = 1.f / maxFPS;
    }
}

float TickClock::dt() const 
{ 
    return elapsed; 
}

void TickClock::set_maxFPS(float new_maxFPS) 
{ 
    maxFPS = new_maxFPS; 
}