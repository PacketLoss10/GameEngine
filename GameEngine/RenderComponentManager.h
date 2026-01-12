#pragma once

#include "ComponentManager.h"
#include "RenderComponent.h"
#include "Sprite.h"
#include "Light.h"

#define RENDER_COMPONENT_MANAGER RenderComponentManager::instance()

class RenderComponentManager :public ComponentManager<RenderComponent>
{
private:
	RenderComponentManager() = default;
	RenderComponentManager(const RenderComponentManager&) = delete;
	RenderComponentManager& operator=(const RenderComponentManager&) = delete;
public:
	static RenderComponentManager& instance();
	void update();
};