#include "Window.h"
#include "World.h"
#include "RenderComponentManager.h"
#include "DragDropManager.h"
#include "TickClock.h"
#include "CollisionComponentManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Card.h"
#include "Library.h"

int main()
{
	Window window = Window(IntVector(1600, 900), "");
	INPUT.set_activeWindow(&window);
	RENDERER.set_activeWindow(&window);

	Library* library1 = new Library();
	library1->set_position(Vector2(1465.f, 730.f));
	Library* library2 = new Library();
	library2->set_position(Vector2(135.f, 730.f));
	WORLD.spawn_entity(library1);
	WORLD.spawn_entity(library2);

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		WORLD.update();
		RENDERER.render();
		UPDATE_DELTA_TIME;
	}

	delete library1;
	delete library2;

	return 0;
}