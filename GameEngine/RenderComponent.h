#pragma once

#include "Component.h"
#include "RenderObject.h"

class RenderComponent :public Component
{
public:
	RenderComponent(Entity* owner);
	virtual ~RenderComponent() = default;

	virtual void finalise() override;
};