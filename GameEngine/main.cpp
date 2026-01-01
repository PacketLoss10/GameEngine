#include "GameWindow.h"
#include "InputHandler.h"
#include "TickClock.h"
#include "Renderer.h"
#include "WorldSystem.h"
#include "Animation.h"
#include "Light.h"

int main()
{
	SET_MAX_FPS(60);

	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), new Sprite("brickwall_diffuse.png", "brickwall_normal.png"));
	WORLD.spawn_actor<Actor>(Transform(FVector(1024.f, 0.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), new Sprite("brickwall_diffuse.png", "brickwall_normal.png"));
	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 1024.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), new Sprite("brickwall_diffuse.png", "brickwall_normal.png"));
	WORLD.spawn_actor<Actor>(Transform(FVector(1024.f, 1024.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), new Sprite("brickwall_diffuse.png","brickwall_normal.png"));
	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(10.f, 10.f)), new Animation("angel_idle.png", IVector(110, 112), IRect(IVector(0, 0), IVector(10, 1)), 10, 10.f, false));
	WORLD.spawn_actor<Actor>(Transform(FVector(100.f, 100.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), new Light(300.f, 1.f, Color(255, 255, 255)));

	while (GAME_WINDOW.is_open())
	{
		GAME_WINDOW.update();
		INPUT.update();
		WORLD.update();

		for (auto c : WORLD.find_all_actors())
		{
			if (auto a = dynamic_cast<Animation*>(c->get_renderable()))
			{
				a->update();
			}
			else if (auto l = dynamic_cast<Light*>(c->get_renderable()))
			{
				c->set_position(INPUT.get_mouse_pos());
			}
		}

		RENDERER.start_render();
		RENDERER.render(WORLD.get_renderData());
		RENDERER.end_render();

		UPDATE_DELTA_TIME;
	}
}