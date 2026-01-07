#include "WorldSystem.h"

WorldSystem::WorldSystem() {}

std::vector<SimulationChunk> WorldSystem::find_chunks_in_radius(FVector origin, float radius) const
{
	std::vector<SimulationChunk> chunks;

	for (auto& [chunk, entities] : chunkMap)
	{
		FVector min = (FVector)chunk.get_coord();
		FVector max = (FVector)chunk.get_coord() + SimulationChunk::chunkSize;

		FVector clamped = FVector(
			std::max(min.x, std::min(origin.x, max.x)),
			std::max(min.y, std::min(origin.y, max.y)));

		if ((origin - clamped).size_squared() <= radius * radius)
			chunks.push_back(chunk);
	}

	return chunks;
}

WorldSystem& WorldSystem::instance()
{
	static WorldSystem instance;
	return instance;
}

void WorldSystem::update()
{
	// Actor removal
	for (Actor* actor : actors)
	{
		if (actor->is_toCull())
			delete actor;
	}
	actors.erase(std::remove_if(actors.begin(), actors.end(),
		[](Actor* actor) { return !actor || (actor && actor->is_toCull()); }), actors.end());

	// Chunk map rebuild
	chunkMap.clear();
	for (Actor* actor : actors)
	{
		chunkMap[SimulationChunk::map_point_to_chunk_coords(actor->get_position())].push_back(actor);
	}

	// Updates
	for (Actor* actor : find_actors_to_update())
	{
		if (actor)
		{
			actor->update();
		}
	}
}

std::vector<RenderObject*> WorldSystem::generate_render_data() const
{
	std::vector<RenderObject*> renderData;

	for (Actor* actor : find_actors_to_render())
	{
		for (RenderObject* graphic : actor->get_graphics())
		{
			renderData.push_back(graphic);
		}
	}

	return renderData;
}

const FVector& WorldSystem::get_view() const
{
	return view;
}

void WorldSystem::set_view(const FVector& new_view)
{
	view = new_view;
}

std::vector<Actor*> WorldSystem::find_actors_to_update() const
{
	std::vector<Actor*> actors;

	for (int dx = -updateDistance; dx <= updateDistance; dx++)
	{
		for (int dy = -updateDistance; dy <= updateDistance; dy++)
		{
			if (auto it = chunkMap.find(SimulationChunk::map_point_to_chunk_coords(view) + IVector(dx, dy)); it != chunkMap.end())
			{
				for (Actor* actor : it->second)
				{
					actors.push_back(actor);
				}
			}
		}
	}

	return actors;
}

std::vector<Actor*> WorldSystem::find_actors_to_render() const
{
	std::vector<Actor*> actors;

	for (int dx = -renderDistance; dx <= renderDistance; dx++)
	{
		for (int dy = -renderDistance; dy <= renderDistance; dy++)
		{
			if (auto it = chunkMap.find(SimulationChunk::map_point_to_chunk_coords(view) + IVector(dx, dy)); it != chunkMap.end())
			{
				for (Actor* actor : it->second)
				{
					actors.push_back(actor);
				}
			}
		}
	}

	return actors;
}

std::vector<Actor*> WorldSystem::find_actors_in_radius(FVector origin, float radius) const
{
	std::vector<Actor*> actors;

	for (const SimulationChunk& chunk : find_chunks_in_radius(origin, radius))
	{
		for (Actor* candidate : chunkMap.at(chunk))
		{
			if ((candidate->get_transform().position - origin).size_squared() > radius * radius) continue;

			actors.push_back(candidate);
		}
	}

	return actors;
}

std::vector<Actor*> WorldSystem::find_all_actors() const
{
	std::vector<Actor*> objects;

	for (auto& [chunk, entities] : chunkMap)
	{
		for (Actor* entity : entities)
		{
			objects.push_back(entity);
		}
	}

	return objects;
}