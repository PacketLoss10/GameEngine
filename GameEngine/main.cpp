#include "GameWindow.h"
#include "InputHandler.h"
#include "TickClock.h"
#include "Renderer.h"
#include "WorldSystem.h"
#include "Animation.h"
#include "Light.h"
#include "JSONFILE.h"

//int main()
//{
//	SET_MAX_FPS(60);
//
//	WORLD.spawn_actor<Actor>(Transform(FVector(0.f, 0.f), FVector(1.f, 0.f), FVector(10.f, 10.f)), std::vector<RenderObject*>{ new Animation("angel_idle.png", IVector(110, 112), IRect(IVector(0, 0), IVector(10, 1)), 10, 10.f, false) });
//	WORLD.spawn_actor<Actor>(Transform(FVector(100.f, 100.f), FVector(1.f, 0.f), FVector(1.f, 1.f)), std::vector<RenderObject*>{ new Light(300.f, 1.f, Color(255, 255, 255)) });
//
//	while (GAME_WINDOW.is_open())
//	{
//		GAME_WINDOW.update();
//		INPUT.update();
//		WORLD.update();
//		for (auto actor : WORLD.find_all_actors())
//		{
//			for (auto g : actor->get_graphics())
//			{
//				if (auto light = dynamic_cast<Light*>(g))
//				{
//					light->set_position(INPUT.get_mouse_pos());
//					if (INPUT.is_button_pressed(Mouse::M1))
//						light->set_brightness(light->get_brightness() + 0.25f);
//					if (INPUT.is_button_pressed(Mouse::M2))
//						light->set_brightness(light->get_brightness() - 0.25f);
//				}
//			}
//		}
//
//		RENDERER.start_render();
//		RENDERER.render(WORLD.generate_render_data());
//		RENDERER.end_render();
//
//		UPDATE_DELTA_TIME;
//	}
//}

#include "Entity.h"
#include "CollisionComponentManager.h"
#include "EntityA.h"
#include "EntityB.h"

int main()
{
	EntityA a;
	EntityB b;
	while (true)
	{
		if(INPUT.is_button_pressed(Mouse::M1))
		COLLISION_COMPONENT_MANAGER.update();
	}
}