#include "Window.h"
#include "World.h"
#include "TickClock.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Card.h"
#include "Library.h"
#include "Graveyard.h"
#include "Exile.h"
#include "CommandZone.h"
#include "CardFactory.h"
#include "GameServer.h"

int main()
{
	std::thread udp_thread(&GameServer::udp_start, &GAME_SERVER);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::thread tcp_thread(&GameServer::tcp_start, &GAME_SERVER);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	Window window = Window(IntVector(1600, 900), "");
	INPUT.set_activeWindow(&window);
	RENDERER.set_activeWindow(&window);

	CardFactory factory;

	Library* library = new Library();
	library->set_position(Vector2(1020.f, 730.f));
	WORLD.spawn_entity(library);

	Graveyard* graveyard = new Graveyard();
	graveyard->set_position(Vector2(1240.f, 730.f));
	WORLD.spawn_entity(graveyard);

	Exile* exile = new Exile();
	exile->set_position(Vector2(1460.f, 730.f));
	WORLD.spawn_entity(exile);

	CommandZone* commandZone = new CommandZone();
	commandZone->set_position(Vector2(1460.f, 400.f));
	WORLD.spawn_entity(commandZone);

	factory.create_deck("infect-deck", library, commandZone);
	library->shuffle();

	while (window.is_open())
	{
		INPUT.update();
		window.update();

		WORLD.update();
		RENDERER.render();
		UPDATE_DELTA_TIME;
	}

	delete library;
	delete graveyard;
	delete exile;
	delete commandZone;

	udp_thread.join();
	tcp_thread.join();

	return 0;
}