#pragma once

#include "EngineUtils.h"
#include "RenderObject.h"

class Sprite :public RenderObject 
{
public:
	Sprite();
	Sprite(std::string path, IVector position, IVector size);
};