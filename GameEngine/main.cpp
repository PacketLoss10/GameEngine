#include "GameWindow.h"
#include "InputHandler.h"
#include "TickClock.h"
#include "Renderer.h"
#include "WorldSystem.h"
#include "Light.h"

int main()
{
	SET_MAX_FPS(60);

	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), new Sprite("brickwall_diffuse.png","brickwall_normal.png"));
	//WORLD.spawn_actor<Actor>(Transform(FVector(500.f, 500.f), FVector(1.f, 0.f), FVector(5.f, 5.f)), new Sprite("sprite.png"));
	WORLD.spawn_actor<Actor>(Transform(FVector(100.f, 100.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), new Light(300.f, 1.f, Color(255, 255, 255)));

	while (GAME_WINDOW.is_open())
	{
		GAME_WINDOW.update();
		INPUT.update();

		WORLD.update();

		for (auto actor : WORLD.find_all_actors())
		{
			if (Light* light = dynamic_cast<Light*>(actor->get_renderable()))
			{
				light->set_position(INPUT.get_mouse_pos());
			}
		}

		RENDERER.start_render();
		RENDERER.render(WORLD.get_renderData());
		RENDERER.end_render();

		UPDATE_DELTA_TIME;
	}
}