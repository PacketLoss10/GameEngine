#include "GameWindow.h"
#include "InputHandler.h"
#include "TickClock.h"
#include "Renderer.h"
#include "WorldSystem.h"
#include "Sprite.h"
#include "LightSource.h"


int main()
{
	SET_MAX_FPS(60);

	Sprite s = Sprite("sprite.png");

	WORLD.spawn_entity(std::make_unique<Actor>(Transform(), new Sprite("sprite.png")));
	WORLD.spawn_entity(std::make_unique<LightSource>(FVector(0.f, 0.f), 200.f, 2.f, Color(0, 0, 0)));

	while (GAME_WINDOW.is_open())
	{
		GAME_WINDOW.update();
		INPUT.update();

		WORLD.update();

		RENDERER.start_render();
		WORLD.render();
		RENDERER.end_render();

		UPDATE_DELTA_TIME;
	}
}