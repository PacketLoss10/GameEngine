#include "NavigationAgent.h"

NavigationAgent::NavigationAgent() {}

void NavigationAgent::update()
{
	if (!task)
		return;

	if (task->wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
	{
		auto result = task->get();
		task.reset();
		if (result)
		{
			currentPath = std::move(result.value());
			if (!currentPath.empty() && (currentPath.top() - position).size_squared() < PATHFINDER.get_stepSize() * PATHFINDER.get_stepSize())
				currentPath.pop();
		}
		else
		{
			while (!currentPath.empty())
				currentPath.pop();
		}
	}

	if (!currentPath.empty())
	{
		if (currentPath.top() != position)
			forward = (currentPath.top() - position).normalised();

		velocity = forward * speed;

		if ((position - currentPath.top()).size_squared() > (velocity * DELTA_TIME).size_squared())
			position = position + velocity * DELTA_TIME;

		else currentPath.pop();
	}
}

void NavigationAgent::start(const FVector& start, const FVector& end)
{
	position = start;
	target = end;
	task = std::async(std::launch::async, [&]() {return PATHFINDER.find_path(start, end); });
}

void NavigationAgent::clear()
{
	while (!currentPath.empty())
		currentPath.pop();
}

bool NavigationAgent::is_finished() const { return !task && currentPath.empty(); }

float NavigationAgent::get_speed() const { return speed; }

void NavigationAgent::set_speed(float new_speed) { speed = new_speed; }