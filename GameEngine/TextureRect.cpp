#include "TextureRect.h"

TextureRect::TextureRect(IntVector position, IntVector size) :position(IntVector(std::max(0, position.x), std::max(0, position.y))), size(IntVector(std::max(1, size.x), std::max(1, size.y))) {}

const IntVector& TextureRect::get_position() const
{
	return position;
}

void TextureRect::set_position(const IntVector& position)
{
	this->position = position;
}

const IntVector& TextureRect::get_size() const
{
	return size;
}

void TextureRect::set_size(const IntVector& size)
{
	this->size = size;
}