#include "CollisionComponentManager.h"
#include "iostream"

void CollisionComponentManager::box_on_box(BoxCollisionComponent* boxA, BoxCollisionComponent* boxB)
{
	FVector axisAX = boxA->get_forward();
	FVector axisAY = boxA->get_forward().perpendicular();
	FVector axisBX = boxB->get_forward();
	FVector axisBY = boxB->get_forward().perpendicular();

	FVector axes[4] = { axisAX,axisAY,axisBX,axisBY };

	FVector halfA = boxA->get_size().component_wise_mult(boxA->get_scale()) * 0.5f;
	FVector halfB = boxB->get_size().component_wise_mult(boxB->get_scale()) * 0.5f;

	for (int i = 0; i < 4; i++)
	{
		FVector axis = axes[i];

		if (axis.size_squared() > 1.01f || axis.size_squared() < 0.99f)
			axis = axis.normalised();

		float cA = boxA->get_position().dot(axis);
		float rA = halfA.x * std::abs(axis.dot(axisAX)) + halfA.y * std::abs(axis.dot(axisAY));

		float cB = boxB->get_position().dot(axis);
		float rB = halfB.x * std::abs(axis.dot(axisBX)) + halfB.y * std::abs(axis.dot(axisBY));

		if (std::abs(cA - cB) > (rA + rB))
			return;
	}

	boxA->on_overlap.invoke(boxA->get_owner(), boxA, boxB->get_owner(), boxB);
	boxB->on_overlap.invoke(boxB->get_owner(), boxB, boxA->get_owner(), boxA);
}

void CollisionComponentManager::circle_on_circle(CircleCollisionComponent* circleA, CircleCollisionComponent* circleB)
{
	auto pointOn = [](CircleCollisionComponent* c, float t)
		{
			return FVector(
				c->get_position().x + cosf(c->get_rotation()) * c->get_radius().x * c->get_scale().x * cosf(t) - sinf(c->get_rotation()) * c->get_radius().y * c->get_scale().y * sinf(t),
				c->get_position().y + sinf(c->get_rotation()) * c->get_radius().x * c->get_scale().x * cosf(t) + cosf(c->get_rotation()) * c->get_radius().y * c->get_scale().y * sinf(t)
			);
		};

	auto pointIn = [](CircleCollisionComponent* c, const FVector& P)
		{
			float ca = cosf(c->get_rotation()), sa = sinf(c->get_rotation());
			FVector d = P - c->get_position();

			float x = ca * d.x + sa * d.y;
			float y = -sa * d.x + ca * d.y;

			float nx = x / (c->get_radius().x * c->get_scale().x);
			float ny = y / (c->get_radius().y * c->get_scale().y);

			return (nx * nx + ny * ny) <= 1.0f;
		};

	for (int i = 0; i < 32; i++)
	{
		float t = (2.0f * mth::pi * i) / 32.0f;
		if (pointIn(circleA, pointOn(circleB, t)))
		{
			circleA->on_overlap.invoke(circleA->get_owner(), circleA, circleB->get_owner(), circleB);
			circleB->on_overlap.invoke(circleB->get_owner(), circleB, circleA->get_owner(), circleA);
			return;
		}
	}

	return;
}

void CollisionComponentManager::circle_on_box(CircleCollisionComponent* circle, BoxCollisionComponent* box)
{
	FVector halfCircle = circle->get_radius().component_wise_mult(circle->get_scale());
	FVector halfBox = box->get_size().component_wise_mult(box->get_scale()) * 0.5f;

	FVector corners[4] =
	{
		{-halfBox.x, -halfBox.y},
		{ halfBox.x, -halfBox.y},
		{ halfBox.x,  halfBox.y},
		{-halfBox.x,  halfBox.y}
	};

	for (int i = 0; i < 4; ++i)
	{
		corners[i] = corners[i].rotated_by(box->get_rotation()) + box->get_position() - circle->get_position();
		corners[i] = corners[i].rotated_by(-circle->get_rotation());
		corners[i] = corners[i].component_wise_div(halfCircle);
	}

	bool inside = true;
	for (int i = 0; i < 4; i++)
	{
		FVector a = corners[i];
		FVector b = corners[(i + 1) & 3];
		FVector edge = b - a;
		FVector normal(edge.y, -edge.x);

		if (normal.dot(a * -1.f) < 0.f)
		{
			inside = false;
			break;
		}
	}

	if (!inside)
	{
		float minDistSq = 100000000.f;

		for (int i = 0; i < 4; i++)
		{
			FVector a = corners[i];
			FVector b = corners[(i + 1) % 4];

			FVector p = a + (b - a) * std::clamp(-a.dot(b - a) / (b - a).dot(b - a), 0.0f, 1.0f);

			minDistSq = std::min(minDistSq, p.dot(p));
		}

		if (minDistSq > 1.0f)
			return;
	}

	circle->on_overlap.invoke(circle->get_owner(), circle, box->get_owner(), box);
	box->on_overlap.invoke(box->get_owner(), box, circle->get_owner(), circle);
}

CollisionComponentManager& CollisionComponentManager::instance()
{
	static CollisionComponentManager instance;
	return instance;
}

void CollisionComponentManager::update()
{
	delete_components();

	for (size_t i = 0; i < components.size(); i++)
	{
		for (size_t j = i + 1; j < components.size(); j++)
		{
			CollisionComponent* compA = components[i];
			CollisionComponent* compB = components[j];

			if (!compA->is_enabled() || !compB->is_enabled())
				continue;

			if (debugMode)
			{

			}

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