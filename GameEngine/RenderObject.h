#pragma once

#include "core.h"

class RenderObject :public Transformable
{
public:
	RenderObject(Transform transform);
	virtual ~RenderObject() = default;
};