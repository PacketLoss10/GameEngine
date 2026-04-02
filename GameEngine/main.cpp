#include "Window.h"
#include "RenderComponentManager.h"
#include "DragDropManager.h"
#include "TickClock.h"
#include "CollisionComponentManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Card.h"

#include "LightComponent.h"
#include "PrimitiveBoxComponent.h"

class LightActor :public Entity
{
private:
	LightComponent* light;
	PrimitiveBoxComponent* box;
public:
	LightActor() :Entity()
	{
		light = new LightComponent(this);
		light->set_brightness(0.5f);
		light->set_color(Color(255, 255, 255));
		light->set_radius(300.f);
		light->set_enabled(true);
		light->finalise();

		box = new PrimitiveBoxComponent(this);
		box->set_size(Vector2(100.f, 100.f));
		box->set_lit(false);
		box->set_fillColor(Color(255, 0, 0));
		box->finalise();
	}
	~LightActor()
	{
		delete light;
		delete box;
	}

	void update_tick() override
	{
		set_position(INPUT.get_mouse_pos());
	}
};

int main()
{
	Window window = Window(IntVector(1600, 900), "");
	INPUT.set_activeWindow(&window);

	std::vector<Card*> cards;
	cards.push_back(new Card("ugin-eye-of-the-storms"));

	LightActor* light = new LightActor();

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		for (Card* card : cards)
		{
			card->update_tick();
			card->input_tick();
		}
		light->update_tick();

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
	delete light;

	return 0;
}