#include "World.h"
#include "CollisionComponentManager.h"
#include "DragDropManager.h"
#include "RenderComponentManager.h"

std::vector<SimulationChunk> World::find_chunks_in_radius(Vector2 origin, float radius) const
{
	std::vector<SimulationChunk> chunks;

	for (const auto& [chunk, entities] : chunkMap)
	{
		Vector2 min = Vector2(static_cast<float>(chunk.get_coord().x), static_cast<float>(chunk.get_coord().y));
		Vector2 max = min + SimulationChunk::get_chunkSize();

		Vector2 clamped = Vector2(
			std::max(min.x, std::min(origin.x, max.x)),
			std::max(min.y, std::min(origin.y, max.y))
		);

		if ((origin - clamped).size_squared() <= radius * radius)
			chunks.push_back(chunk);
	}

	return chunks;
}

World& World::instance()
{
	static World instance;
	return instance;
}

void World::update()
{
	// DESPAWNING ENTITIES WITH "toDespawn" FLAG
	despawn_entities();

	// REBUILD CHUNK MAP
	chunkMap.clear();
	for (Entity* entity : allEntities)
	{
		if (!entity)
			continue;

		SimulationChunk chunk = SimulationChunk(SimulationChunk::map_to_chunk(entity->get_position()));
		chunkMap[chunk].push_back(entity);
	}

	// UPDATES
	//
	//
	//
	COLLISION_COMPONENT_MANAGER.update();
	DRAG_DROP_MANAGER.update();
	RENDER_COMPONENT_MANAGER.update();
	for (Entity* entity : allEntities)
	{
		entity->update_tick();
		entity->input_tick();
		entity->physics_tick();
	}

}

void World::spawn_entity(Entity* entity)
{
	if (!entity)
		return;

	allEntities.push_back(entity);
	entity->spawned = true;
	entity->toDespawn = false;
	entity->on_spawn.invoke();
}

void World::despawn_entities()
{
	allEntities.erase(
		std::remove_if(allEntities.begin(), allEntities.end(),
			[](Entity* entity) {
				if (!entity)
					return true;

				if (entity->toDespawn)
				{
					entity->spawned = false;
					entity->on_despawn.invoke();
					return true;
				}
				return false;
			}
		), allEntities.end()
	);
}

std::vector<Entity*> World::entities_in_radius(const Vector2& origin, float radius) const
{
	std::vector<Entity*> entities;

	for (const SimulationChunk& chunk : find_chunks_in_radius(origin, radius))
	{
		for (Entity* entity : chunkMap.at(chunk))
		{
			if (!entity)
				continue;

			if ((entity->get_position() - origin).size_squared() > radius * radius)
				continue;

			entities.push_back(entity);
		}
	}

	return entities;
}

std::vector<Entity*> World::all_entities() const
{
	std::vector<Entity*> entities;

	for (const auto& [chunk, chunkEntities] : chunkMap)
	{
		for (Entity* entity : chunkEntities)
		{
			if (!entity)
				continue;

			entities.push_back(entity);
		}
	}

	return entities;
}

const Vector2& World::get_view() const
{
	return view;
}

void World::set_view(const Vector2& view)
{
	this->view = view;
}