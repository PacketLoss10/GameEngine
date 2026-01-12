#pragma once

#include "Component.h"
#include "Transformable.h"

class RenderComponent :public Component, public Transformable
{
public:
	RenderComponent() = default;
	RenderComponent(Transform transform);
	virtual ~RenderComponent() = default;
};