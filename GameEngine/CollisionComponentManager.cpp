#include "CollisionComponentManager.h"
#include "InputHandler.h"
#include "iostream"

void CollisionComponentManager::box_on_box(BoxCollisionComponent* boxA, BoxCollisionComponent* boxB)
{
	Vector2 axisAX = boxA->get_worldForward();
	Vector2 axisAY = boxA->get_worldForward().perpendicular();
	Vector2 axisBX = boxB->get_worldForward();
	Vector2 axisBY = boxB->get_worldForward().perpendicular();

	Vector2 axes[4] = { axisAX,axisAY,axisBX,axisBY };

	Vector2 halfA = boxA->get_size().component_wise_mult(boxA->get_worldScale()) * 0.5f;
	Vector2 halfB = boxB->get_size().component_wise_mult(boxB->get_worldScale()) * 0.5f;

	for (int i = 0; i < 4; i++)
	{
		Vector2 axis = axes[i];

		if (axis.size_squared() > 1.01f || axis.size_squared() < 0.99f)
			axis = axis.normalised();

		float cA = boxA->get_worldPosition().dot(axis);
		float rA = halfA.x * std::abs(axis.dot(axisAX)) + halfA.y * std::abs(axis.dot(axisAY));

		float cB = boxB->get_worldPosition().dot(axis);
		float rB = halfB.x * std::abs(axis.dot(axisBX)) + halfB.y * std::abs(axis.dot(axisBY));

		if (std::abs(cA - cB) > (rA + rB))
		{
			if (boxA->is_overlapping(boxB))
			{
				boxA->remove_overlap(boxB);
				boxA->on_end_overlap.invoke(boxA, boxB->get_owner(), boxB);
			}
			if (boxB->is_overlapping(boxA))
			{
				boxB->remove_overlap(boxA);
				boxB->on_end_overlap.invoke(boxB, boxA->get_owner(), boxA);
			}

			return;
		}
	}

	boxA->on_overlap.invoke(boxA, boxB->get_owner(), boxB);
	if (!boxA->is_overlapping(boxB))
	{
		boxA->add_overlap(boxB);
		boxA->on_begin_overlap.invoke(boxA, boxB->get_owner(), boxB);
	}
	boxB->on_overlap.invoke(boxB, boxA->get_owner(), boxA);
	if (!boxB->is_overlapping(boxA))
	{
		boxB->add_overlap(boxA);
		boxB->on_begin_overlap.invoke(boxB, boxA->get_owner(), boxA);
	}

	return;
}

void CollisionComponentManager::circle_on_circle(CircleCollisionComponent* circleA, CircleCollisionComponent* circleB)
{
	auto pointOn = [](CircleCollisionComponent* c, float t)
		{
			return Vector2(
				c->get_worldPosition().x + cosf(c->get_worldRotation()) * c->get_radius().x * c->get_worldScale().x * cosf(t) - sinf(c->get_worldRotation()) * c->get_radius().y * c->get_worldScale().y * sinf(t),
				c->get_worldPosition().y + sinf(c->get_worldRotation()) * c->get_radius().x * c->get_worldScale().x * cosf(t) + cosf(c->get_worldRotation()) * c->get_radius().y * c->get_worldScale().y * sinf(t)
			);
		};

	auto pointIn = [](CircleCollisionComponent* c, const Vector2& P)
		{
			float ca = cosf(c->get_worldRotation()), sa = sinf(c->get_worldRotation());
			Vector2 d = P - c->get_worldPosition();

			float x = ca * d.x + sa * d.y;
			float y = -sa * d.x + ca * d.y;

			float nx = x / (c->get_radius().x * c->get_worldScale().x);
			float ny = y / (c->get_radius().y * c->get_worldScale().y);

			return (nx * nx + ny * ny) <= 1.0f;
		};

	for (int i = 0; i < 32; i++)
	{
		float t = (2.0f * 3.14159265358979f * i) / 32.0f;
		if (pointIn(circleA, pointOn(circleB, t)))
		{
			circleA->on_overlap.invoke(circleA, circleB->get_owner(), circleB);
			if (!circleA->is_overlapping(circleB))
			{
				circleA->add_overlap(circleB);
				circleA->on_begin_overlap.invoke(circleA, circleB->get_owner(), circleB);
			}
			circleB->on_overlap.invoke(circleB, circleA->get_owner(), circleA);
			if (!circleB->is_overlapping(circleA))
			{
				circleB->add_overlap(circleA);
				circleB->on_begin_overlap.invoke(circleB, circleA->get_owner(), circleA);
			}

			return;
		}
	}

	if (circleA->is_overlapping(circleB))
	{
		circleA->remove_overlap(circleB);
		circleA->on_end_overlap.invoke(circleA, circleB->get_owner(), circleB);
	}
	if (circleB->is_overlapping(circleA))
	{
		circleB->remove_overlap(circleA);
		circleB->on_end_overlap.invoke(circleB, circleA->get_owner(), circleA);
	}

	return;
}

void CollisionComponentManager::circle_on_box(CircleCollisionComponent* circle, BoxCollisionComponent* box)
{
	Vector2 halfCircle = circle->get_radius().component_wise_mult(circle->get_worldScale());
	Vector2 halfBox = box->get_size().component_wise_mult(box->get_worldScale()) * 0.5f;

	Vector2 corners[4] =
	{
		{-halfBox.x, -halfBox.y},
		{ halfBox.x, -halfBox.y},
		{ halfBox.x,  halfBox.y},
		{-halfBox.x,  halfBox.y}
	};

	for (int i = 0; i < 4; ++i)
	{
		corners[i] = corners[i].rotated_by(box->get_worldRotation()) + box->get_worldPosition() - circle->get_worldPosition();
		corners[i] = corners[i].rotated_by(-circle->get_worldRotation());
		corners[i] = corners[i].component_wise_div(halfCircle);
	}

	bool inside = true;
	for (int i = 0; i < 4; i++)
	{
		Vector2 a = corners[i];
		Vector2 b = corners[(i + 1) & 3];
		Vector2 edge = b - a;
		Vector2 normal(edge.y, -edge.x);

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
			Vector2 a = corners[i];
			Vector2 b = corners[(i + 1) % 4];

			Vector2 p = a + (b - a) * std::clamp(-a.dot(b - a) / (b - a).dot(b - a), 0.0f, 1.0f);

			minDistSq = std::min(minDistSq, p.dot(p));
		}

		if (minDistSq > 1.0f)
		{
			if (circle->is_overlapping(box))
			{
				circle->remove_overlap(box);
				circle->on_end_overlap.invoke(circle, box->get_owner(), box);
			}
			if (box->is_overlapping(circle))
			{
				box->remove_overlap(circle);
				box->on_end_overlap.invoke(box, circle->get_owner(), circle);
			}

			return;
		}
	}

	circle->on_overlap.invoke(circle, box->get_owner(), box);
	if (!circle->is_overlapping(box))
	{
		circle->add_overlap(box);
		circle->on_begin_overlap.invoke(circle, box->get_owner(), box);
	}
	box->on_overlap.invoke(box, circle->get_owner(), circle);
	if (!box->is_overlapping(circle))
	{
		box->add_overlap(circle);
		box->on_begin_overlap.invoke(box, circle->get_owner(), circle);
	}

	return;
}

void CollisionComponentManager::point_in_box(BoxCollisionComponent* box)
{
	Vector2 mousePos = INPUT.get_mouse_pos();

	Vector2 halfBox = box->get_size().component_wise_mult(box->get_worldScale()) * 0.5f;
	Vector2 dif = mousePos - box->get_worldPosition();

	float xr = dif.dot(box->get_worldForward());
	float yr = dif.perpendicular().dot(box->get_worldForward());

	if (fabs(xr) <= halfBox.x && fabs(yr) <= halfBox.y)
	{
		box->on_mouse_overlap.invoke(box, mousePos);
		if (!box->is_mouseOverlapping())
		{
			box->set_mouseOverlapping(true);
			box->on_mouse_begin_overlap.invoke(box, mousePos);
		}

		return;
	}
	else
	{
		if (box->is_mouseOverlapping())
		{
			box->set_mouseOverlapping(false);
			box->on_mouse_end_overlap.invoke(box, mousePos);
		}

		return;
	}
}

void CollisionComponentManager::point_in_circle(CircleCollisionComponent* circle)
{
	Vector2 mousePos = INPUT.get_mouse_pos();

	Vector2 halfCircle = circle->get_radius().component_wise_mult(circle->get_worldScale());
	Vector2 dif = mousePos - circle->get_worldPosition();

	float xr = dif.dot(circle->get_worldForward());
	float yr = dif.perpendicular().dot(circle->get_worldForward());

	float n = (xr * xr) / (halfCircle.x * halfCircle.x) + (yr * yr) / (halfCircle.y * halfCircle.y);

	if (n <= 1.f)
	{
		circle->on_mouse_overlap.invoke(circle, mousePos);
		if (!circle->is_mouseOverlapping())
		{
			circle->set_mouseOverlapping(true);
			circle->on_mouse_begin_overlap.invoke(circle, mousePos);
		}

		return;
	}
	else
	{
		if (circle->is_mouseOverlapping())
		{
			circle->set_mouseOverlapping(false);
			circle->on_mouse_end_overlap.invoke(circle, mousePos);
		}

		return;
	}
}

CollisionComponentManager& CollisionComponentManager::instance()
{
	static CollisionComponentManager instance;
	return instance;
}

void CollisionComponentManager::update()
{
	despawn_components();

	for (CollisionComponent* comp : components)
	{
		if (!comp || !comp->is_enabled())
			continue;

		if(BoxCollisionComponent* box = dynamic_cast<BoxCollisionComponent*>(comp))
		{
			point_in_box(box);
		}
		else if (CircleCollisionComponent* circle = dynamic_cast<CircleCollisionComponent*>(comp))
		{
			point_in_circle(circle);
		}
	}

	for (size_t i = 0; i < components.size(); i++)
	{
		for (size_t j = i + 1; j < components.size(); j++)
		{
			CollisionComponent* compA = components[i];
			CollisionComponent* compB = components[j];

			if (!compA || !compB || !compA->is_enabled() || !compB->is_enabled())
				continue;

			if (CircleCollisionComponent* circleA = dynamic_cast<CircleCollisionComponent*>(compA))
			{
				if (CircleCollisionComponent* circleB = dynamic_cast<CircleCollisionComponent*>(compB))
				{
					circle_on_circle(circleA, circleB);
				}
				else if (BoxCollisionComponent* boxB = dynamic_cast<BoxCollisionComponent*>(compB))
				{
					circle_on_box(circleA, boxB);
				}
			}
			else if (BoxCollisionComponent* boxA = dynamic_cast<BoxCollisionComponent*>(compA))
			{
				if (CircleCollisionComponent* circleB = dynamic_cast<CircleCollisionComponent*>(compB))
				{
					circle_on_box(circleB, boxA);
				}
				else if (BoxCollisionComponent* boxB = dynamic_cast<BoxCollisionComponent*>(compB))
				{
					box_on_box(boxA, boxB);
				}
			}
		}
	}
}