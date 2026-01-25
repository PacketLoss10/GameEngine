#include "InputHandler.h"
#include "CollisionComponentManager.h"
#include "EntityA.h"
#include "EntityB.h"
#include "TickClock.h"
#include "Color.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "PrimitiveBoxShape.h"
#include "PrimitiveCircleShape.h"
#include "PrimitiveLineShape.h"
#include "Window.h"
#include "Light.h"
#include "Renderer.h"
#include "RenderComponentManager.h"
#include "NavigationComponentManager.h"
#include "NavMesh.h"

int main()
{
	Window window = Window(IVector(1600, 900), "");
	INPUT.set_activeWindow(&window);
	std::vector<FVector> nodes;
	NavMesh navmesh;
	EntityA a;

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		if (INPUT.is_button_pressed(Mouse::M1))
		{
			a.get_nav()->start(a.get_position(), INPUT.get_mouse_pos(), navmesh);
		}
		a.update();
		if (INPUT.is_button_pressed(Mouse::M2))
		{
			nodes.push_back(INPUT.get_mouse_pos());
		}

		navmesh.clear();
		for (int i = 0; nodes.size() >= 3 && i < static_cast<int>(nodes.size()) - 2; i++)
		{
			Triangle tri;
			tri.A = nodes[0];
			tri.B = nodes[i + 1];
			tri.C = nodes[i + 2];
			navmesh.add_triangle(tri);
		}

		NAVIGATION_COMPONENT_MANAGER.update();
		RENDER_COMPONENT_MANAGER.update();
		RENDERER.set_navmesh(navmesh);
		RENDERER.render(window);
		UPDATE_DELTA_TIME;
	}

	return 0;
}