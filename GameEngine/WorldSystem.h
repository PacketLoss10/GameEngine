#pragma once

#include "EngineUtils.h"
#include "ChunkMap.h"
#include "Actor.h"

#define WORLD WorldSystem::instance()

class WorldSystem
{
private:
	std::vector<std::unique_ptr<Actor>> entities;
	ChunkMap chunkMap;
	FVector cameraPosition = FVector(0.f, 0.f);
	WorldSystem();
	WorldSystem(const WorldSystem&) = delete;
	WorldSystem& operator=(const WorldSystem&) = delete;
public:
	static WorldSystem& instance();
	
	void update();

	template<IsActor T, typename... Args>
	void spawn_actor(Args&&... actorArgs) 
	{
		static_assert(std::is_constructible_v<T, Args...>, "spawn_actor parameters do not match actor constructor");

		entities.push_back(std::make_unique<T>(std::forward<Args>(actorArgs)...));
	}

	std::vector<Renderable*> get_renderData() const;

	const ChunkMap& get_chunkMap() const;
	void set_cameraPosition(FVector new_cameraPosition);

	std::vector<Actor*> actors_to_update(FVector view) const { return chunkMap.find_actors_to_update(view); }
	std::vector<Actor*> actors_to_render(FVector view) const { return chunkMap.find_actors_to_render(view); }

	std::vector<Actor*> find_actors_in_radius(Actor* actor, float radius) const { return chunkMap.find_actors_in_radius(actor, radius); }
	template<IsActor T>
	std::vector<T*> find_actors_in_radius_of_type(Actor* actor, float radius) const { return chunkMap.find_actors_in_radius_of_type<T>(actor, radius); }

	std::vector<Actor*> find_actors_in_radius(FVector origin, float radius) const { return chunkMap.find_actors_in_radius(origin, radius); }
	template<IsActor T>
	std::vector<T*> find_actors_in_radius_of_type(FVector origin, float radius) const { return chunkMap.find_actors_in_radius_of_type<T>(origin, radius); }

	std::vector<Actor*> find_all_actors() const { return chunkMap.find_all_actors(); }
	template<IsActor T>
	std::vector<T*> find_all_actors_of_type() const { return chunkMap.find_all_actors_of_type<T>(); }
};