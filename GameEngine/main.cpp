#include "InputHandler.h"
#include "CollisionComponentManager.h"
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
#include "SFML/Network.hpp"
#include "Card.h"

int main()
{
	Window window = Window(IVector(1600, 900), "");
	INPUT.set_activeWindow(&window);

	Card* card1 = new Card();
	Card* card2 = new Card();

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		card1->update_tick();
		card1->input_tick();

		card2->update_tick();

		RENDER_COMPONENT_MANAGER.update();
		COLLISION_COMPONENT_MANAGER.update();
		RENDERER.render(window);
		UPDATE_DELTA_TIME;
	}

	return 0;
}