#pragma once

#include "utility"
#include "vector"

class Entity;

class Component
{
private:
protected:
	Entity* owner = nullptr;
	bool enabled = true;
	bool toDelete = false;
public:
	Component(Entity* owner, bool enabled);
	Component() = default;
	virtual ~Component() = default;

	Entity* get_owner() const;
	void set_owner(Entity* owner);

	bool is_enabled() const;
	void set_enable(bool enabled);

	bool is_toDelete() const;
	void set_toDelete(bool toDelete);
};

template<typename T>
concept IsComponent = std::is_base_of<Component, T>::value;