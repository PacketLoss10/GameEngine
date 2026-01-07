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

	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), std::vector<RenderObject*>{ new Sprite("brickwall_diffuse.png", "brickwall_normal.png") });
	WORLD.spawn_actor<Actor>(Transform(FVector(1024.f, 0.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), std::vector<RenderObject*>{ new Sprite("brickwall_diffuse.png", "brickwall_normal.png") });
	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 1024.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), std::vector<RenderObject*>{ new Sprite("brickwall_diffuse.png", "brickwall_normal.png") });
	WORLD.spawn_actor<Actor>(Transform(FVector(1024.f, 1024.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), std::vector<RenderObject*>{ new Sprite("brickwall_diffuse.png","brickwall_normal.png") });
	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(10.f, 10.f)), std::vector<RenderObject*>{ new Animation("angel_idle.png", IVector(110, 112), IRect(IVector(0, 0), IVector(10, 1)), 10, 10.f, false) });
	WORLD.spawn_actor<Actor>(Transform(FVector(100.f, 100.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), std::vector<RenderObject*>{ new Light(300.f, 1.f, Color(255, 255, 255)) });

	while (GAME_WINDOW.is_open())
	{
		GAME_WINDOW.update();
		INPUT.update();
		WORLD.update();

		RENDERER.start_render();
		RENDERER.render(WORLD.generate_render_data());
		RENDERER.end_render();

		UPDATE_DELTA_TIME;
	}
}