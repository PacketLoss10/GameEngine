#pragma once

#include "Transform.h"
#include "Color.h"
#include "Window.h"

struct Triangle
{
	FVector A = FVector();
	FVector B = FVector();
	FVector C = FVector();

	Triangle() = default;
	Triangle(FVector A, FVector B, FVector C) :A(A), B(B), C(C) {}

	float area() const
	{
		return std::abs((A.x - C.x) * (B.y - C.y) - (B.x - C.x) * (A.y - C.y));
	}
};

class NavMesh
{
private:
	std::vector<Triangle> navmesh;
public:
	bool contains_point(const FVector& point) const
	{
		for (const Triangle& tri : navmesh)
		{
			float area0 = tri.area();

			float area1 = Triangle(tri.A, tri.B, point).area();
			float area2 = Triangle(tri.B, tri.C, point).area();
			float area3 = Triangle(tri.C, tri.A, point).area();

			return std::abs(area1 + area2 + area3 - area0) < 0.01f;
		}
		return false;
	}
	void add_triangle(const Triangle& tri)
	{
		navmesh.push_back(tri);
	}
	void clear()
	{
		navmesh.clear();
	}
	void render(Window& window)
	{
		for (const Triangle& tri : navmesh)
		{
			sf::ConvexShape shape = sf::ConvexShape(3);
			shape.setPoint(0, tri.A);
			shape.setPoint(1, tri.B);
			shape.setPoint(2, tri.C);
			shape.setOutlineThickness(2.f);
			shape.setOutlineColor(Color(0, 200, 255, 190));
			shape.setFillColor(Color(0, 170, 170, 120));
			window.display(shape, nullptr);
		}
	}
	bool empty() const
	{
		return navmesh.empty();
	}
};