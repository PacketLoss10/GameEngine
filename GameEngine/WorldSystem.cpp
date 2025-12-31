#include "WorldSystem.h"

WorldSystem::WorldSystem() {}

WorldSystem& WorldSystem::instance()
{
	static WorldSystem instance;
	return instance;
}

void WorldSystem::update()
{
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[](const std::unique_ptr<Actor>& entity) { return !entity.get() || (entity.get() && entity->is_toCull()); }), entities.end());

	chunkMap.clear();
	for (auto& entity : entities)
		if (entity.get())
			chunkMap.add_actor(entity.get());

	for (auto& entity : chunkMap.actors_to_update(cameraPosition))
		if (entity)
		{
			entity->update();
		}
}

void WorldSystem::render()
{
	for (auto& entity : chunkMap.actors_to_render(cameraPosition))
		if (entity)
			entity->render();
}

void WorldSystem::spawn_entity(std::unique_ptr<Actor> entity) 
{
	entities.push_back(std::move(entity)); 
}

const ChunkMap& WorldSystem::get_chunkMap() const 
{
	return chunkMap;
}

void WorldSystem::set_cameraPosition(FVector new_cameraPosition) 
{
	cameraPosition = new_cameraPosition; 
}