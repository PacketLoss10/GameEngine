#pragma once

#include "EngineUtils.h"

#define UPDATE_DELTA_TIME TickClock::instance().update()
#define DELTA_TIME TickClock::instance().dt()
#define SET_MAX_FPS(fps) TickClock::instance().set_maxFPS(fps)

class TickClock 
{
private:
	sf::Clock clock;
	float elapsed = 0.f;
	float maxFPS = 125.f;
	TickClock() = default;
	TickClock(const TickClock&) = delete;
	TickClock& operator=(const TickClock&) = delete;
public:
	static TickClock& instance();
	void update();
	float dt() const;
	void set_maxFPS(float new_maxFPS);
};