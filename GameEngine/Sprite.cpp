#include "Sprite.h"

Sprite::Sprite() :RenderObject() {}

Sprite::Sprite(std::string path, IVector position, IVector size) :RenderObject(FrameData(path, IRect(position, size))) {}