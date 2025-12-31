#include "ChunkMap.h"

std::vector<SimulationChunk> ChunkMap::find_chunks_in_radius(FVector origin, float radius) const
{
	std::vector<SimulationChunk> chunks;

	for(auto& [chunk, entities] : map)
	{
		FVector min = (FVector)chunk.get_coord();
		FVector max = (FVector)chunk.get_coord() + SimulationChunk::chunkSize;

		FVector clamped = FVector(
			std::max(min.x, std::min(origin.x, max.x)),
			std::max(min.y, std::min(origin.y, max.y)));

		if((origin - clamped).size_squared() <= radius * radius)
			chunks.push_back(chunk);
	}

	return chunks;
}

void ChunkMap::clear()
{
	map.clear(); 
}

void ChunkMap::add_actor(Actor* actor)
{ 
	map[SimulationChunk::map_point_to_chunk_coords(actor->get_transform().position)].push_back(actor);
}

std::vector<Actor*> ChunkMap::find_actors_to_update(FVector view) const
{
	std::vector<Actor*> actors;

	for (int dx = -simulationDistance; dx <= simulationDistance; dx++)
	{
		for (int dy = -simulationDistance; dy <= simulationDistance; dy++)
		{
			if (auto it = map.find(SimulationChunk::map_point_to_chunk_coords(view) + IVector(dx, dy)); it != map.end())
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

std::vector<Actor*> ChunkMap::find_actors_to_render(FVector view) const 
{
	std::vector<Actor*> actors;

	for (int dx = -renderDistance; dx <= renderDistance; dx++)
	{
		for (int dy = -renderDistance; dy <= renderDistance; dy++)
		{
			if (auto it = map.find(SimulationChunk::map_point_to_chunk_coords(view) + IVector(dx, dy)); it != map.end())
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

std::vector<Actor*> ChunkMap::find_actors_in_radius(Actor* actor, float radius) const
{
	std::vector<Actor*> actors;

	for (const SimulationChunk& chunk : find_chunks_in_radius(actor->get_transform().position, radius))
	{
		for(Actor* candidate:map.at(chunk))
		{
			if (candidate == actor || (candidate->get_transform().position - actor->get_transform().position).size_squared() > radius * radius) continue;

			actors.push_back(candidate);
		}
	}

	return actors;
}

std::vector<Actor*> ChunkMap::find_actors_in_radius(FVector origin, float radius) const 
{
	std::vector<Actor*> actors;

	for(const SimulationChunk& chunk: find_chunks_in_radius(origin, radius))
	{
		for(Actor* candidate:map.at(chunk))
		{
			if ((candidate->get_transform().position - origin).size_squared() > radius * radius) continue;
			
			actors.push_back(candidate);
		}
	}

	return actors;
}

std::vector<Actor*> ChunkMap::find_all_actors() const 
{
	std::vector<Actor*> objects;

	for (auto& [chunk, entities] : map)
	{
		for (Actor* entity : entities)
		{
			objects.push_back(entity);
		}
	}

	return objects;
}