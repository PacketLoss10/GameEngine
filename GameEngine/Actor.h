#pragma once

#include "core.h"
#include "RenderObject.h"
#include "CollisionArea.h"
#include "SLObject.h"

class Actor: public Transformable
{
protected:
	std::vector<RenderObject*> graphics;
	CollisionArea* collision = nullptr;
	bool toCull = false;
public:
	Actor(Transform transform, std::vector<RenderObject*> graphics);
	~Actor();
	virtual void update();
	CollisionArea* get_collision() const;
	const std::vector<RenderObject*>& get_graphics() const;
	bool is_toCull() const;
	void set_toCull(bool new_toCull);
};