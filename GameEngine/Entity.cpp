#include "Entity.h"

bool Entity::is_toDelete() const
{
	return toDelete;
}

void Entity::set_toDelete(bool toDelete)
{
	this->toDelete = toDelete;
}

void Entity::cull()
{

}

void Entity::update_tick()
{

}

void Entity::physics_tick()
{

}

void Entity::input_tick()
{

}