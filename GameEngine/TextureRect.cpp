#include "TextureRect.h"

TextureRect::TextureRect(IntVector position, IntVector size) :position(IntVector(std::max(0, position.x), std::max(0, position.y))), size(IntVector(std::max(1, size.x), std::max(1, size.y))) {}
