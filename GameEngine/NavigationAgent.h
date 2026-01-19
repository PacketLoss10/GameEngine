#pragma once

#include "PathFinder.h"
#include "TickClock.h"
#include "chrono"
#include "future"

class NavigationAgent
{
private:
	float speed = 0.f;
	FVector position = FVector(0.f, 0.f);
	FVector target = FVector(0.f, 0.f);
	FVector velocity = FVector(0.f, 0.f);
	FVector forward = FVector(1.f, 0.f);
	std::stack<FVector> currentPath;
	std::optional<std::future<std::optional<std::stack<FVector>>>> task;
public:
	NavigationAgent();
	void update();
	void start(const FVector& start, const FVector& end);
	void clear();
	bool is_finished() const;
	float get_speed() const;
	void set_speed(float speed);
	const FVector& get_forward() const;
	const FVector& get_position() const;
};