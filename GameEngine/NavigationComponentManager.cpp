#include "NavigationComponentManager.h"

NavigationComponentManager& NavigationComponentManager::instance()
{
	static NavigationComponentManager instance;
	return instance;
}

void NavigationComponentManager::update()
{
	for (NavigationComponent* comp : components)
	{
		comp->update();
	}
}