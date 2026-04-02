#pragma once

#include "Component.h"
#include "RenderData.h"

class RenderComponent :public Component
{
public:
	RenderComponent(Entity* owner);
	virtual ~RenderComponent() = default;

	virtual void finalise() override;

	virtual RenderDataType get_type() const = 0;
};