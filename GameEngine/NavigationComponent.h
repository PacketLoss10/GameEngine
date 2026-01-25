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
	FVector position = FVector(0.f, 0.f);
	FVector target = FVector(0.f, 0.f);
	FVector velocity = FVector(0.f, 0.f);
	FVector forward = FVector(1.f, 0.f);
	std::stack<FVector> path;
	std::optional<std::future<std::optional<std::stack<FVector>>>> task;
public:
	NavigationComponent() = default;
	NavigationComponent(Entity* owner, bool enabled, float speed);
	void init() override;
	void update();
	void start(const FVector& start, const FVector& end, const NavMesh& navmesh);
	void clear();
	bool is_finished() const;
	float get_speed() const;
	void set_speed(float speed);
	const FVector& get_forward() const;
	const FVector& get_position() const;
};