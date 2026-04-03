#pragma once

#include "Transformable.h"
#include "Delegate.h"

class World;

class Entity :public Transformable
{
private:
	friend class World;
	friend class Component;
	bool toDespawn = false;
	bool spawned = false;
protected:
	Delegate<> on_despawn;
	Delegate<> on_spawn;
public:
	virtual ~Entity() = default;

	void despawn();

	virtual void update_tick();
	virtual void physics_tick();
	virtual void input_tick();
};