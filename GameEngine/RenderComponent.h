#pragma once

#include "Component.h"
#include "RenderObject.h"

class RenderComponent :public Component, public RenderObject
{
public:
	RenderComponent() = default;
	RenderComponent(Entity* owner, bool enabled, Transform transform);
	virtual ~RenderComponent() = default;
};