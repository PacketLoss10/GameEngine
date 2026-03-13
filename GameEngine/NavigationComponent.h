#pragma once

#include "Component.h"
#include "Transform.h"
#include "chrono"
#include "future"
#include "stack"

class NavMesh;

class NavigationComponent: public Component
{
private:
	float speed = 0.f;
	Vector2 position = Vector2(0.f, 0.f);
	Vector2 target = Vector2(0.f, 0.f);
	Vector2 velocity = Vector2(0.f, 0.f);
	Vector2 forward = Vector2(1.f, 0.f);
	std::stack<Vector2> path;
	std::optional<std::future<std::optional<std::stack<Vector2>>>> task;
public:
	NavigationComponent(Entity* owner);
	virtual ~NavigationComponent() = default;
	virtual void finalise() override;
	void update();
	void start(const Vector2& start, const Vector2& end, const NavMesh& navmesh);
	void clear();
	bool is_finished() const;
	float get_speed() const;
	void set_speed(float speed);
	const Vector2& get_forward() const;
	const Vector2& get_position() const;
};