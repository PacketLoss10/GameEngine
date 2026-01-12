#pragma once

#include "SFML/Graphics.hpp"

class Timer
{
private:
	sf::Clock timer;
	float duration = 0.f;
	bool oneShot = false;
public:
	Timer();
	Timer(float duration, bool oneShot, bool autoStart);
	void start();
	void stop();
	void reset();
	void restart();
	bool timeout();
	float time_elapsed() const;

	float get_duration() const;
	void set_duration(float new_duration);

	bool is_oneShot() const;
	void set_oneShot(bool new_oneShot);
};