#include "Window.h"
#include "RenderComponentManager.h"
#include "DragDropManager.h"
#include "TickClock.h"
#include "CollisionComponentManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Card.h"

int main()
{
	Window window = Window(IntVector(1600, 900), "");
	INPUT.set_activeWindow(&window);

	std::vector<Card*> cards;
	cards.push_back(new Card("ugin-eye-of-the-storms"));

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		for (Card* card : cards)
		{
			card->update_tick();
			card->input_tick();
		}

		if (INPUT.is_key_pressed(Keyboard::Space))
		{
			cards.push_back(new Card("ugin-eye-of-the-storms"));
		}

		RENDER_COMPONENT_MANAGER.update();
		COLLISION_COMPONENT_MANAGER.update();
		DRAG_DROP_MANAGER.update();
		RENDERER.render(window);
		UPDATE_DELTA_TIME;
	}

	for (Card* card : cards)
	{
		delete card;
	}

	return 0;
}