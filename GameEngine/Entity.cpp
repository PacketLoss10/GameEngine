#include "Entity.h"
#include "Component.h"

void Component::spawn()
{
	spawned = true;
}

void Entity::despawn()
{
	toDespawn = true;
}

void Entity::update_tick() {}

void Entity::physics_tick() {}

void Entity::input_tick() {}