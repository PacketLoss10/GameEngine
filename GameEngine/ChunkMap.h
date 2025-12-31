#pragma once

#include "SimulationChunk.h"
#include "Actor.h"

template<typename T>
concept IsActor = std::is_base_of<Actor, T>::value;

class ChunkMap
{
private:
	const int simulationDistance = 5;
	const int renderDistance = 3;
	std::unordered_map<SimulationChunk, std::vector<Actor*>> map;
	std::vector<SimulationChunk> find_chunks_in_radius(FVector origin, float radius) const;
public:
	void clear();
	void add_actor(Actor* actor);

	std::vector<Actor*> find_actors_to_update(FVector view) const;
	std::vector<Actor*> find_actors_to_render(FVector view) const;

	std::vector<Actor*> find_actors_in_radius(Actor* actor, float radius) const;
	template<IsActor T>
	std::vector<T*> find_actors_in_radius_of_type(Actor* actor, float radius) const
	{
		std::vector<T*> actors;

		for (const SimulationChunk& chunk : find_chunks_in_radius(actor->get_transform().position, radius))
		{
			for (Actor* candidate : map.at(chunk))
			{
				if (candidate == actor || (candidate->get_transform().position - actor->get_transform().position).size_squared() > radius * radius)
					continue;

				if (T* casted = dynamic_cast<T*>(candidate))
					actors.push_back(casted);
			}
		}

		return actors;
	}

	std::vector<Actor*> find_actors_in_radius(FVector origin, float radius) const;
	template<IsActor T>
	std::vector<T*> find_actors_in_radius_of_type(FVector origin, float radius) const
	{
		std::vector<T*> actors;

		for (const SimulationChunk& chunk : find_chunks_in_radius(origin, radius))
		{
			for (Actor* candidate : map.at(chunk))
			{
				if ((candidate->get_transform().position - origin).size_squared() > radius * radius)
					continue;
				
				if (T* casted = dynamic_cast<T*>(candidate))
					actors.push_back(casted);
			}
		}

		return actors;
	}

	std::vector<Actor*> find_all_actors() const;
	template<IsActor T>
	std::vector<T*> find_all_actors_of_type() const
	{
		std::vector<T*> actors;
		for (auto& [chunk, entities] : map)
		{
			for (Actor* candidate : entities)
			{
				if (T* casted = dynamic_cast<T*>(candidate))
					actors.push_back(casted);
			}
		}

		return actors;
	}
};