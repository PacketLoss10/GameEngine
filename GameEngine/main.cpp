#include "Window.h"
#include "RenderComponentManager.h"
#include "DragDropManager.h"
#include "TickClock.h"
#include "CollisionComponentManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Library.h"
#include "Card.h"

int main()
{
	Window window = Window(IntVector(1600, 900), "");
	INPUT.set_activeWindow(&window);

	Library* library = new Library();
	library->set_position(Vector2(800.f, 600.f));
	for (int i = 0; i < 60; i++)
	{
		library->add_card(new Card("ugin-eye-of-the-storms"), LibraryPosition::Top);
	}
	std::vector<Card*> cards;

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		for (Card* card : cards)
		{
			card->update_tick();
			card->input_tick();
		}

		if (library->get_collision()->is_mouseOverlapping() && INPUT.is_button_pressed(Mouse::M2))
		{
			cards.push_back(library->draw_card());
		}

		RENDER_COMPONENT_MANAGER.update();
		COLLISION_COMPONENT_MANAGER.update();
		DRAG_DROP_MANAGER.update();
		RENDERER.render(window);
		UPDATE_DELTA_TIME;
	}

	delete library;

	return 0;
}