#include "IntRect.h"

IntRect::IntRect(IntVector position, IntVector size) :position(position), size(size) {}

std::optional<IntRect> IntRect::find_intersection(const IntRect& other) const
{
	int x = std::max(position.x, other.position.x);
	int y = std::max(position.y, other.position.y);
	int w = std::min(position.x + size.x, other.position.x + other.size.x) - x;
	int h = std::min(position.y + size.y, other.position.y + other.size.y) - y;

	if (w <= 0 || h <= 0)
		return std::nullopt;

	return IntRect(IntVector(x, y), IntVector(w, h));
}