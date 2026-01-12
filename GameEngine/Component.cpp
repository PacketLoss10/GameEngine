#include "Component.h"

Component::Component(Entity* owner, bool enabled) :owner(owner), enabled(enabled) {}

Entity* Component::get_owner() const
{
	return owner;
}

void Component::set_owner(Entity* owner)
{
	this->owner = owner;
}

bool Component::is_enabled() const
{
	return enabled;
}

void Component::set_enable(bool enabled)
{
	this->enabled = enabled;
}

bool Component::is_toDelete() const
{
	return toDelete;
}

void Component::set_toDelete(bool toDelete)
{
	this->toDelete = toDelete;
}