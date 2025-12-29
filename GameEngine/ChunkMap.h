#pragma once

#include "SimulationChunk.h"
#include "Actor.h"

class ChunkMap
{
private:
	const int simulationDistance = 5;
	const int renderDistance = 3;
	std::unordered_map<SimulationChunk, std::vector<Actor*>> map;
	std::vector<SimulationChunk> find_chunks_in_radius(FVector origin, float radius) const;
	template<typename... T>
	bool is_of_type(Actor* actor) const
	{
		return ((dynamic_cast<T*>(actor) != nullptr) || ...);
	}
public:
	void clear();
	void add_actor(Actor* actor);

	std::vector<Actor*> actors_to_update(FVector view) const;
	std::vector<Actor*> actors_to_render(FVector view) const;

	std::vector<Actor*> find_actors_in_radius(Actor* actor, float radius) const;
	std::vector<Actor*> find_actors_in_radius(FVector origin, float radius) const;

	std::vector<Actor*> find_all_actors() const;

	template<typename... T>
	std::vector<Actor*> find_actors_of_type_in_radius(Actor* actor, float radius) const
	{
		std::vector<Actor*> actors;

		for (auto chunk : find_chunks_in_radius(actor->get_transform().position, radius))
		{
			for (auto candidate : map.at(chunk))
			{
				if (candidate == actor || (candidate->get_transform().position - actor->get_transform().position).size_squared()() > radius * radius) continue;

				if (is_of_type<T...>(candidate))
					actors.push_back(candidate);
			}
		}

		return actors;
	}

	template<typename... T>
	std::vector<Actor*> find_actors_of_type_in_radius(FVector origin, float radius) const
	{
		std::vector<Actor*> actors;

		for (auto chunk : find_chunks_in_radius(origin, radius))
		{
			for (auto candidate : map.at(chunk))
			{
				if ((candidate->get_transform().position - origin).size_squared() > radius * radius) continue;

				if (is_of_type<T...>(candidate))
					actors.push_back(candidate);
			}
		}

		return actors;
	}

	template<typename... T>
	std::vector<Actor*> find_all_actors_of_type() const
	{
		std::vector<Actor*> actors;
		for (auto& [chunk, entities] : map)
		{
			for (auto entity : entities)
			{
				if (is_of_type<T...>(entity))
					actors.push_back(entity);
			}
		}

		return actors;
	}
};