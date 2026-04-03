//std::vector<RenderObject*> generate_render_data() const;
//std::vector<Actor*> find_actors_to_update() const;
//std::vector<Actor*> find_actors_to_render() const;

#pragma once

#include <unordered_map>
#include "SimulationChunk.h"
#include "Entity.h"

template<typename T>
concept entitytype = std::is_base_of<Entity, T>::value;

class World
{
private:
	World() = default;
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	std::vector<SimulationChunk> find_chunks_in_radius(Vector2 origin, float radius) const;

	std::vector<Entity*> allEntities;
	std::unordered_map<SimulationChunk, std::vector<Entity*>> chunkMap;

	Vector2 view = Vector2();
	const int updateDistance = 5;
	const int renderDistance = 5;
public:
	static World& instance();

	void update();

	void spawn_entity(Entity* entity);

	void despawn_entities();

	std::vector<Entity*> entities_in_radius(const Vector2& origin, float radius) const;
	std::vector<Entity*> all_entities() const;

	template<entitytype T>
	std::vector<T*> entities_of_type_in_radius(const Vector2& origin, float radius) const
	{
		std::vector<T*> entities;

		for (const SimulationChunk& chunk : find_chunks_in_radius(origin, radius))
		{
			for (Entity* entity : chunkMap.at(chunk))
			{
				if (!entity)
					continue;

				if ((entity->get_position() - origin).size_squared() > radius * radius)
					continue;

				if (T* casted = dynamic_cast<T*>(entity))
					entities.push_back(casted);
			}
		}

		return entities;
	}

	template<entitytype T>
	std::vector<T*> all_entities_of_type() const
	{
		std::vector<T*> entities;

		for (const auto& [chunk, chunkEntities] : chunkMap)
		{
			for (Entity* entity : chunkEntities)
			{
				if (!entity)
					continue;

				if (T* casted = dynamic_cast<T*>(entity))
					entities.push_back(casted);
			}
		}

		return entities;
	}

	const Vector2& get_view() const;
	void set_view(const Vector2& view);
};