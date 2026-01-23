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

int main()
{
	SET_MAX_FPS(6000);
	Window window = Window(IVector(1600, 900), "");
	INPUT.set_activeWindow(&window);
	EntityA a;

	PrimitiveCircleShape c(FVector(200.f, 300.f), Transform(FVector(200.f, 200.f), FVector(1.f, 0.f), FVector(1.f, 1.f)));

	while (window.is_open())
	{
		//std::cout << 1.f / DELTA_TIME << std::endl;
		INPUT.update();
		window.update();

		if (INPUT.is_button_pressed(Mouse::M2))
		{
			a.get_nav()->start(a.get_position(), INPUT.get_mouse_pos());
		}
		a.update();


		NAVIGATION_COMPONENT_MANAGER.update();
		RENDER_COMPONENT_MANAGER.update();
		RENDERER.render(window);
		UPDATE_DELTA_TIME;
	}

	return 0;
}