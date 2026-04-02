//#pragma once
//
//#include "Transform.h"
//#include "Color.h"
//#include "GameWindow.h"
//
//class SimulationChunk 
//{
//private:
//	IntVector coord = IntVector(0, 0);
//	Color fillColor = Color(0, 0, 0, 0);
//	Color outlineColor = Color(255, 255, 255, 255);
//	bool visible = false;
//public:
//	static Vector2 chunkSize;
//	SimulationChunk(IntVector coord);
//	bool operator==(const SimulationChunk& other) const;
//	void render() const;
//	static IntVector map_point_to_chunk_coords(const Vector2& point);
//	const IntVector& get_coord() const;
//	const Color& get_fillColor() const;
//	void set_fillColor(const Color& new_fillColor);
//	const Color& get_outlineColor() const;
//	void set_outlineColor(const Color& new_outlineColor);
//	bool is_visible() const;
//	void set_visible(bool new_visible);
//};
//
//namespace std 
//{
//	template<>
//	struct hash<SimulationChunk> 
//	{
//		size_t operator()(const SimulationChunk& key) const noexcept 
//		{ 
//			return std::hash<int>()(key.get_coord().x) ^ (std::hash<int>()(key.get_coord().y) << 1); 
//		}
//	};
//}