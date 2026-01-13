#pragma once

class Entity;

class Component
{
protected:
	Entity* owner = nullptr;
	bool enabled = true;
	bool toDelete = false;
public:
	Component() = default;
	Component(Entity* owner, bool enabled);
	virtual ~Component() = default;

	virtual void init() {};

	Entity* get_owner() const;
	void set_owner(Entity* owner);

	bool is_enabled() const;
	void set_enable(bool enabled);

	bool is_toDelete() const;
	void set_toDelete(bool toDelete);
};