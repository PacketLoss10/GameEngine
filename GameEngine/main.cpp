#include "GameWindow.h"
#include "InputHandler.h"
#include "TickClock.h"
#include "Renderer.h"
#include "WorldSystem.h"
#include "LightSource.h"

int main()
{
	SET_MAX_FPS(60);

	WORLD.spawn_entity(std::make_unique<Actor>(Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(5.f, 5.f)), new Sprite("energyblade.png")));
	WORLD.spawn_entity(std::make_unique<Actor>(Transform(FVector(500.f, 500.f), FVector(1.f, 0.f), FVector(5.f, 5.f)), new Sprite("sprite.png")));
	WORLD.spawn_entity(std::make_unique<LightSource>(FVector(0.f, 0.f), 200.f, 1.f, Color(255, 255, 255)));
	WORLD.spawn_entity(std::make_unique<LightSource>(FVector(0.f, 0.f), 500.f, 1.f, Color(255, 0, 0)));

	while (GAME_WINDOW.is_open())
	{
		GAME_WINDOW.update();
		INPUT.update();

		WORLD.update();

		WORLD.find_all_actors_of_type<LightSource>()[0]->set_position(INPUT.get_mouse_pos());


		RENDERER.start_render();
		WORLD.render();
		RENDERER.end_render();

		UPDATE_DELTA_TIME;
	}
}