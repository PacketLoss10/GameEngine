#include "TextureRect.h"

TextureRect::TextureRect(IVector position, IVector size) :position(IVector(std::max(0, position.x), std::max(0, position.y))), size(IVector(std::max(1, size.x), std::max(1, size.y))) {}
