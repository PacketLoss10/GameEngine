#pragma once

class Entity
{
protected:
	bool toDelete = false;
public:
	virtual ~Entity() = default;
	bool is_toDelete() const;
	void set_toDelete(bool toDelete);
	virtual void cull();
	virtual void update_tick();
	virtual void physics_tick();
	virtual void input_tick();
};