#pragma once

#include "EngineUtils.h"

class RenderObject :public Transformable
{
public:
	RenderObject(Transform transform);
	virtual ~RenderObject() = default;
};