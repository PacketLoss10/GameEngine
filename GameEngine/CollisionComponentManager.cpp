#include "CollisionComponentManager.h"
#include "iostream"

void CollisionComponentManager::box_on_box(BoxCollisionComponent* boxA, BoxCollisionComponent* boxB)
{
	FVector axes[4];
	axes[0] = boxA->get_forward() * boxA->get_scale().x;
	axes[1] = perpendicular(boxA->get_forward()) * boxA->get_scale().y;
	axes[2] = boxB->get_forward() * boxB->get_scale().x;
	axes[3] = perpendicular(boxB->get_forward()) * boxB->get_scale().y;

	FVector halfA = boxA->get_size() * 0.5f;
	FVector halfB = boxB->get_size() * 0.5f;

	for (int i = 0; i < 4; i++)
	{
		FVector axis = axes[i];

		float rA = halfA.x * std::abs(axis.dot(boxA->get_forward())) +
			halfA.y * std::abs(axis.dot(perpendicular(boxA->get_forward())));

		float projA = axis.dot(boxA->get_position());
		float minA = projA - rA;
		float maxA = projA + rA;

		float rB = halfB.x * std::abs(axis.dot(boxB->get_forward())) +
			halfB.y * std::abs(axis.dot(perpendicular(boxB->get_forward())));

		float projB = axis.dot(boxB->get_position());
		float minB = projB - rB;
		float maxB = projB + rB;

		if (maxA < minB || maxB < minA)
			return;
	}

	boxA->on_overlap.invoke(boxA->get_owner(), boxA, boxB->get_owner(), boxB);
	boxB->on_overlap.invoke(boxB->get_owner(), boxB, boxA->get_owner(), boxA);
}

void CollisionComponentManager::circle_on_circle(CircleCollisionComponent* circleA, CircleCollisionComponent* circleB)
{
	FVector axes[4];
	axes[0] = circleA->get_forward() * circleA->get_scale().x;
	axes[1] = perpendicular(circleA->get_forward()) * circleA->get_scale().y;
	axes[2] = circleB->get_forward() * circleB->get_scale().x;
	axes[3] = perpendicular(circleB->get_forward()) * circleB->get_scale().y;

	FVector halfA = circleA->get_radius();
	FVector halfB = circleB->get_radius();

	for (int i = 0; i < 4; i++)
	{
		FVector axis = axes[i];

		float rA = circleA->get_radius().x * std::abs(axis.dot(circleA->get_forward())) +
			circleA->get_radius().y * std::abs(axis.dot(perpendicular(circleA->get_forward())));
		float projA = axis.dot(circleA->get_position());
		float minA = projA - rA;
		float maxA = projA + rA;

		float rB = circleB->get_radius().x * std::abs(axis.dot(circleB->get_forward())) +
			circleB->get_radius().y * std::abs(axis.dot(perpendicular(circleB->get_forward())));
		float projB = axis.dot(circleB->get_position());
		float minB = projB - rB;
		float maxB = projB + rB;

		if (maxA < minB || maxB < minA)
			return;
	}

	circleA->on_overlap.invoke(circleA->get_owner(), circleA, circleB->get_owner(), circleB);
	circleB->on_overlap.invoke(circleB->get_owner(), circleB, circleA->get_owner(), circleA);
}

void CollisionComponentManager::circle_on_box(CircleCollisionComponent* circle, BoxCollisionComponent* box)
{
	FVector axes[4];
	axes[0] = circle->get_forward() * circle->get_scale().x;
	axes[1] = perpendicular(circle->get_forward()) * circle->get_scale().y;
	axes[2] = box->get_forward() * box->get_scale().x;
	axes[3] = perpendicular(box->get_forward()) * box->get_scale().y;

	FVector halfBox = box->get_size() * 0.5f;

	for (int i = 0; i < 4; i++)
	{
		FVector axis = axes[i];

		float rCircle = circle->get_radius().x * std::abs(axis.dot(circle->get_forward())) +
			circle->get_radius().y * std::abs(axis.dot(perpendicular(circle->get_forward())));
		float projCircle = axis.dot(circle->get_position());
		float minCircle = projCircle - rCircle;
		float maxCircle = projCircle + rCircle;

		float rBox = halfBox.x * std::abs(axis.dot(box->get_forward())) +
			halfBox.y * std::abs(axis.dot(perpendicular(box->get_forward())));
		float projBox = axis.dot(box->get_position());
		float minBox = projBox - rBox;
		float maxBox = projBox + rBox;

		if (maxCircle < minBox || maxBox < minCircle)
			return;
	}

	circle->on_overlap.invoke(circle->get_owner(), circle, box->get_owner(), box);
	box->on_overlap.invoke(box->get_owner(), box, circle->get_owner(), circle);
}

FVector CollisionComponentManager::perpendicular(const FVector& v) const
{
	return FVector(-v.y, v.x); 
}


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
					circle_on_circle(circleA, circleB);
					continue;
				}
				if (BoxCollisionComponent* boxB = dynamic_cast<BoxCollisionComponent*>(compB))
				{
					circle_on_box(circleA, boxB);
					continue;
				}
			}
			if (BoxCollisionComponent* boxA = dynamic_cast<BoxCollisionComponent*>(compA))
			{
				if (CircleCollisionComponent* circleB = dynamic_cast<CircleCollisionComponent*>(compB))
				{
					circle_on_box(circleB, boxA);
					continue;
				}
				if (BoxCollisionComponent* boxB = dynamic_cast<BoxCollisionComponent*>(compB))
				{
					box_on_box(boxA, boxB);
					continue;
				}
			}
		}
	}
}
