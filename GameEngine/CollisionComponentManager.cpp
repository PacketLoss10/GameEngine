#include "CollisionComponentManager.h"

CollisionComponentManager& CollisionComponentManager::instance()
{
	static CollisionComponentManager instance;
	return instance;
}

void CollisionComponentManager::update()
{
	delete_components();

	for (CollisionComponent* compA : components)
	{
		if (!compA->is_enabled())
			return;

		std::cout << "component detected" << std::endl;

		for (CollisionComponent* compB : components)
		{
			if (!compB->is_enabled())
				return;

			if (compA == compB)
				continue;

			if (CircleCollisionComponent* circleA = dynamic_cast<CircleCollisionComponent*>(compA))
			{
				if (CircleCollisionComponent* circleB = dynamic_cast<CircleCollisionComponent*>(compB))
				{
					if ((circleA->get_position() - circleB->get_position()).size() <= circleA->get_radius() + circleB->get_radius())
					{
						circleA->on_overlap.invoke(circleA->get_owner(), circleA, circleB->get_owner(), circleB);
						circleB->on_overlap.invoke(circleB->get_owner(), circleB, circleA->get_owner(), circleA);
					}

					continue;
				}
				if (BoxCollisionComponent* boxB = dynamic_cast<BoxCollisionComponent*>(compB))
				{
					FVector min = boxB->get_position() - boxB->get_size() / 2.f;
					FVector max = boxB->get_position() + boxB->get_size() / 2.f;

					FVector clamped(
						std::max(min.x, std::min(circleA->get_position().x, max.x)),
						std::max(min.y, std::min(circleA->get_position().y, max.y)));

					if ((circleA->get_position() - clamped).size_squared() <= circleA->get_radius() * circleA->get_radius())
					{
						circleA->on_overlap.invoke(circleA->get_owner(), circleA, boxB->get_owner(), boxB);
						boxB->on_overlap.invoke(boxB->get_owner(), boxB, circleA->get_owner(), circleA);
					}

					continue;
				}
			}
			if (BoxCollisionComponent* boxA = dynamic_cast<BoxCollisionComponent*>(compA))
			{
				if (CircleCollisionComponent* circleB = dynamic_cast<CircleCollisionComponent*>(compB))
				{
					FVector min = boxA->get_position() - boxA->get_size() / 2.f;
					FVector max = boxA->get_position() + boxA->get_size() / 2.f;

					FVector clamped(
						std::max(min.x, std::min(circleB->get_position().x, max.x)),
						std::max(min.y, std::min(circleB->get_position().y, max.y)));

					if ((circleB->get_position() - clamped).size_squared() <= circleB->get_radius() * circleB->get_radius())
					{
						boxA->on_overlap.invoke(boxA->get_owner(), boxA, circleB->get_owner(), circleB);
						circleB->on_overlap.invoke(circleB->get_owner(), circleB, boxA->get_owner(), boxA);
					}

					continue;
				}
				if (BoxCollisionComponent* boxB = dynamic_cast<BoxCollisionComponent*>(compB))
				{
					if (FRect(boxA->get_position() - boxA->get_size() / 2.f, boxA->get_size()).find_intersection(FRect(boxB->get_position() - boxB->get_size() / 2.f, boxB->get_size())).has_value())
					{
						boxA->on_overlap.invoke(boxA->get_owner(), boxA, boxB->get_owner(), boxB);
						boxB->on_overlap.invoke(boxB->get_owner(), boxB, boxA->get_owner(), boxA);
					}

					continue;
				}
			}
		}
	}
}
