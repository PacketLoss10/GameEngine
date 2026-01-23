#pragma once

#include "ComponentManager.h"
#include "NavigationComponent.h"

#define NAVIGATION_COMPONENT_MANAGER NavigationComponentManager::instance()

class NavigationComponentManager :public ComponentManager<NavigationComponent>
{
private:
	NavigationComponentManager() = default;
	NavigationComponentManager(const NavigationComponentManager&) = delete;
	NavigationComponentManager& operator=(const NavigationComponentManager&) = delete;
public:
	static NavigationComponentManager& instance();
	void update();
};