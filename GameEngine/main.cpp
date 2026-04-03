#include "Window.h"
#include "World.h"
#include "RenderComponentManager.h"
#include "DragDropManager.h"
#include "TickClock.h"
#include "CollisionComponentManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Card.h"

#include <iostream>
int main()
{
	Window window = Window(IntVector(1600, 900), "");
	INPUT.set_activeWindow(&window);
	RENDERER.set_activeWindow(&window);

	Card* card = new Card("ugin-eye-of-the-storms");

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		if (INPUT.is_key_pressed(Keyboard::Space))
		{
			World::instance().spawn_entity(card);
		}

		WORLD.update();
		RENDERER.render();
		UPDATE_DELTA_TIME;
	}

	delete card;

	return 0;
}