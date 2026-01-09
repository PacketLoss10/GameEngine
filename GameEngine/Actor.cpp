#include "Actor.h"
#include "Animation.h"

Actor::Actor(Transform transform, std::vector<RenderObject*> graphics):Transformable(transform),graphics(graphics) {}

Actor::~Actor()
{
	for (RenderObject* graphic : graphics)
		delete graphic;
	delete collision;
}

void Actor::update()
{
	for (RenderObject* graphic : graphics)
	{
		graphic->set_transform(transform);
		if (Animation* animation = dynamic_cast<Animation*>(graphic))
		{
			animation->update();
		}
	}
}

CollisionArea* Actor::get_collision() const
{
	return collision;
}

const std::vector<RenderObject*>& Actor::get_graphics() const
{
	return graphics;
}

bool Actor::is_toCull() const
{
	return toCull;
}

void Actor::set_toCull(bool new_toCull)
{
	toCull = new_toCull;
}