#include "SimulationChunk.h"

Vector2 SimulationChunk::chunkSize;

SimulationChunk::SimulationChunk(IntVector coord) :coord(coord) {}

IntVector SimulationChunk::map_to_chunk(const Vector2& position)
{
	return IntVector(
		static_cast<int>(std::floor(position.x / chunkSize.x)),
		static_cast<int>(std::floor(position.y / chunkSize.y))
	);
}

const IntVector& SimulationChunk::get_coord() const
{
	return coord;
}

const Vector2& SimulationChunk::get_chunkSize()
{
	return chunkSize;
}