#include "Timer.h"

Timer::Timer() {}

Timer::Timer(float duration, bool oneShot, bool autoStart) :duration(duration), oneShot(oneShot) 
{
	if (!autoStart)
		timer.reset();
}

void Timer::start()
{
	timer.start();
}

void Timer::stop()
{
	timer.stop();
}

void Timer::reset()
{
	timer.reset();
}

void Timer::restart()
{
	timer.restart();
}

bool Timer::timeout()
{
	return time_elapsed() >= duration;
}

float Timer::get_duration() const
{
	return duration;
}

void Timer::set_duration(float new_duration)
{
	duration = new_duration;
}

bool Timer::is_oneShot() const
{
	return oneShot;
}

void Timer::set_oneShot(bool new_oneShot)
{
	oneShot = new_oneShot;
}

float Timer::time_elapsed() const
{
	return timer.getElapsedTime().asSeconds();
}