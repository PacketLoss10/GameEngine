#pragma once

#include "EngineUtils.h"
#include "GameWindow.h"

class SimulationChunk 
{
private:
	IVector coord = IVector(0, 0);
	Color fillColor = Color(0, 0, 0, 0);
	Color outlineColor = Color(255, 255, 255, 255);
	bool visible = false;
public:
	static FVector chunkSize;
	SimulationChunk(IVector coord);
	bool operator==(const SimulationChunk& other) const;
	void render() const;
	static IVector map_point_to_chunk_coords(const FVector& point);
	const IVector& get_coord() const;
	const Color& get_fillColor() const;
	void set_fillColor(const Color& new_fillColor);
	const Color& get_outlineColor() const;
	void set_outlineColor(const Color& new_outlineColor);
	bool is_visible() const;
	void set_visible(bool new_visible);
};

namespace std 
{
	template<>
	struct hash<SimulationChunk> 
	{
		size_t operator()(const SimulationChunk& key) const noexcept 
		{ 
			return std::hash<int>()(key.get_coord().x) ^ (std::hash<int>()(key.get_coord().y) << 1); 
		}
	};
}