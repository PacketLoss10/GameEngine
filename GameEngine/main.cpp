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
#include "DragDropManager.h"
#include "NavMesh.h"
#include "SFML/Network.hpp"
#include "Card.h"

int main()
{
	Window window = Window(IVector(1600, 900), "");
	INPUT.set_activeWindow(&window);

	std::vector<Card*> cards;
	cards.push_back(new Card());

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		for (Card* card : cards)
		{
			card->update_tick();
			card->input_tick();
		}

		if (INPUT.is_button_pressed(Mouse::M3))
		{
			cards.push_back(new Card());
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