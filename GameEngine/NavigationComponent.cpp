#include "NavigationComponent.h"
#include "NavigationComponentManager.h"
#include "PathFinder.h"
#include "TickClock.h"

NavigationComponent::NavigationComponent(Entity* owner, bool enabled, float speed) :Component(owner, enabled), speed(speed) {}

void NavigationComponent::init()
{
	NAVIGATION_COMPONENT_MANAGER.register_component(this);
}

void NavigationComponent::update()
{
	if (!task)
		return;

	if (task->wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
	{
		auto result = task->get();
		task.reset();
		if (result)
		{
			path = std::move(result.value());
			if (!path.empty() && (path.top() - position).size_squared() < PATHFINDER.get_stepSize() * PATHFINDER.get_stepSize())
				path.pop();
		}
		else
		{
			clear();
		}
	}

	if (!path.empty())
	{
		if (path.top() != position)
			forward = (path.top() - position).normalised();

		velocity = forward * speed;

		if ((position - path.top()).size_squared() > (velocity * DELTA_TIME).size_squared())
			position = position + velocity * DELTA_TIME;

		else path.pop();
	}
}

void NavigationComponent::start(const FVector& start, const FVector& end)
{
	position = start;
	target = end;
	task = std::async(std::launch::async, [&]() {return PATHFINDER.find_path(start, end); });
}

void NavigationComponent::clear()
{
	while (!path.empty())
		path.pop();
}

bool NavigationComponent::is_finished() const 
{
	return !task && path.empty();
}

float NavigationComponent::get_speed() const 
{ 
	return speed;
}

void NavigationComponent::set_speed(float speed) 
{ 
	this->speed = speed; 
}

const FVector& NavigationComponent::get_forward() const
{
	return forward;
}

const FVector& NavigationComponent::get_position() const
{
	return position;
}