#include "SimulationChunk.h"

SimulationChunk::SimulationChunk(IVector coord) :coord(coord) {}

bool SimulationChunk::operator==(const SimulationChunk& other) const
{
	return coord == other.get_coord();
}

void SimulationChunk::render() const 
{
	if (!visible) return;

	sf::RectangleShape shape = sf::RectangleShape(chunkSize);
	shape.setPosition((FVector)coord);
	shape.setFillColor(fillColor);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(outlineColor);

	GAME_WINDOW.render(shape, nullptr);
}

IVector SimulationChunk::map_point_to_chunk_coords(const FVector& point) 
{
	return IVector(
		static_cast<int>(std::floor(point.x / chunkSize.x)),
		static_cast<int>(std::floor(point.y / chunkSize.y))
	);
}

const IVector& SimulationChunk::get_coord() const 
{
	return coord; 
}

const Color& SimulationChunk::get_fillColor() const 
{
	return fillColor; 
}

void SimulationChunk::set_fillColor(const Color& new_fillColor) 
{
	fillColor = new_fillColor; 
}

const Color& SimulationChunk::get_outlineColor() const 
{
	return outlineColor; 
}

void SimulationChunk::set_outlineColor(const Color& new_outlineColor) 
{
	outlineColor = new_outlineColor; 
}

bool SimulationChunk::is_visible() const 
{
	return visible; 
}

void SimulationChunk::set_visible(bool new_visible) 
{
	visible = new_visible; 
}

FVector SimulationChunk::chunkSize = FVector(500.f, 500.f);