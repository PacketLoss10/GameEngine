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

void CollisionComponentManager::circle_on_circle(
	CircleCollisionComponent* A,
	CircleCollisionComponent* B)
{
	// --- effective radii ---
	FVector rA = A->get_radius().component_wise_mult(A->get_scale());
	FVector rB = B->get_radius().component_wise_mult(B->get_scale());

	// --- transform B center into A space ---
	FVector d = (B->get_position() - A->get_position())
		.rotated_by(-A->get_forward().angle())
		.component_wise_div(rA); // A becomes unit circle

	// --- relative rotation ---
	float relAngle = B->get_forward().angle() - A->get_forward().angle();

	// --- axes of B in A space ---
	FVector ux = FVector(1, 0).rotated_by(relAngle);
	FVector uy = FVector(0, 1).rotated_by(relAngle);

	// scale axes by relative radii
	float a = rB.x / rA.x;
	float b = rB.y / rA.y;

	ux = ux.normalised();
	uy = uy.normalised();

	// --- project center of B into B's axes ---
	float px = d.dot(ux);
	float py = d.dot(uy);

	// --- Newton iteration to find closest point on ellipse B to origin ---
	float t = 0.f;
	for (int i = 0; i < 8; ++i)
	{
		float ct = cosf(t);
		float st = sinf(t);

		float ex = a * ct;
		float ey = b * st;

		float f = (a * a - b * b) * ct * st - px * a * st + py * b * ct;
		float df = (a * a - b * b) * (ct * ct - st * st) - px * a * ct - py * b * st;

		t -= f / df;
	}

	// --- compute closest point ---
	float cx = a * cosf(t);
	float cy = b * sinf(t);

	float distSq = (cx - px) * (cx - px) + (cy - py) * (cy - py);

	// --- overlap check ---
	if (distSq <= 1.f)
	{
		A->on_overlap.invoke(A->get_owner(), A, B->get_owner(), B);
		B->on_overlap.invoke(B->get_owner(), B, A->get_owner(), A);
	}
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
		corners[i] = corners[i].rotated_by(box->get_forward().angle()) + box->get_position() - circle->get_position();
		corners[i] = corners[i].rotated_by(-circle->get_forward().angle());
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
