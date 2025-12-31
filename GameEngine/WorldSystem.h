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
	void render();
	void spawn_entity(std::unique_ptr<Actor> entity);
	const ChunkMap& get_chunkMap() const;
	void set_cameraPosition(FVector new_cameraPosition);

	std::vector<Actor*> actors_to_update(FVector view) const { return chunkMap.actors_to_update(view); }
	std::vector<Actor*> actors_to_render(FVector view) const { return chunkMap.actors_to_render(view); }

	std::vector<Actor*> find_actors_in_radius(Actor* actor, float radius) const { return chunkMap.find_actors_in_radius(actor, radius); }
	std::vector<Actor*> find_actors_in_radius(FVector origin, float radius) const { return chunkMap.find_actors_in_radius(origin, radius); }

	std::vector<Actor*> find_all_actors() const { return chunkMap.find_all_actors(); }

	template<typename... T>
	std::vector<Actor*> find_actors_of_type_in_radius(Actor* actor, float radius) const { return chunkMap.find_actors_of_type_in_radius<T...>(actor, radius); }
	template<typename... T>
	std::vector<Actor*> find_actors_of_type_in_radius(FVector origin, float radius) const { return chunkMap.find_actors_of_type_in_radius<T...>(origin, radius); }

	template<typename... T>
	std::vector<Actor*> find_all_actors_of_type() const { return chunkMap.find_all_actors_of_type<T...>(); }
};