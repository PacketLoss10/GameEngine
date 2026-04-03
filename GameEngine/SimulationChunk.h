#pragma once

#include "IntVector.h"
#include "Vector2.h"

class SimulationChunk
{
private:
	IntVector coord = IntVector();
	static Vector2 chunkSize;
public:
	SimulationChunk(IntVector coord);
	
	bool operator==(const SimulationChunk& other) const
	{
		return coord.x == other.coord.x && coord.y == other.coord.y;
	}

	static IntVector map_to_chunk(const Vector2& position);

	const IntVector& get_coord() const;
	static const Vector2& get_chunkSize();
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