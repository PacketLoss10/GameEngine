//#pragma once
//
//#include "core.h"
//#include "SimulationChunk.h"
//
//#define WORLD WorldSystem::instance()
//
//template<typename T>
//concept actortype = std::is_base_of<Actor, T>::value;
//
//class WorldSystem
//{
//private:
//	std::vector<Actor*> actors;
//	FVector view = FVector(0.f, 0.f);
//	const int updateDistance = 5;
//	const int renderDistance = 3;
//	std::unordered_map<SimulationChunk, std::vector<Actor*>> chunkMap;
//	WorldSystem();
//	WorldSystem(const WorldSystem&) = delete;
//	WorldSystem& operator=(const WorldSystem&) = delete;
//	std::vector<SimulationChunk> find_chunks_in_radius(FVector origin, float radius) const;
//public:
//	static WorldSystem& instance();
//	
//	void update();
//
//	template<actortype T, typename... Args>
//	void spawn_actor(Args&&... actorArgs) 
//	{
//		static_assert(std::is_constructible_v<T, Args...>, "spawn_actor parameters do not match actor constructor");
//
//		actors.push_back(new T(std::forward<Args>(actorArgs)...));
//	}
//
//	std::vector<RenderObject*> generate_render_data() const;
//
//	const FVector& get_view() const;
//	void set_view(const FVector& new_view);
//
//	std::vector<Actor*> find_actors_to_update() const;
//	std::vector<Actor*> find_actors_to_render() const;
//
//	std::vector<Actor*> find_actors_in_radius(FVector origin, float radius) const;
//	template<actortype T>
//	std::vector<T*> find_actors_in_radius_of_type(FVector origin, float radius) const
//	{
//		std::vector<T*> actors;
//
//		for (const SimulationChunk& chunk : find_chunks_in_radius(origin, radius))
//		{
//			for (Actor* candidate : chunkMap.at(chunk))
//			{
//				if ((candidate->get_transform().position - origin).size_squared() > radius * radius)
//					continue;
//
//				if (T* casted = dynamic_cast<T*>(candidate))
//					actors.push_back(casted);
//			}
//		}
//
//		return actors;
//	}
//
//	std::vector<Actor*> find_all_actors() const;
//	template<actortype T>
//	std::vector<T*> find_all_actors_of_type() const
//	{
//		std::vector<T*> actors;
//
//		for (auto& [chunk, entities] : chunkMap)
//		{
//			for (Actor* candidate : entities)
//			{
//				if (T* casted = dynamic_cast<T*>(candidate))
//					actors.push_back(casted);
//			}
//		}
//
//		return actors;
//	}
//};