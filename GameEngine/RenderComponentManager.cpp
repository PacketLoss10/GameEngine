#include "RenderComponentManager.h"

RenderComponentManager& RenderComponentManager::instance()
{
	static RenderComponentManager instance;
	return instance;
}

void RenderComponentManager::update()
{
	delete_components();

	std::vector<Sprite*> sprites;

	std::vector<Light*> lights;

	for (RenderComponent* component : components)
	{
		if (Sprite* sprite = dynamic_cast<Sprite*>(component))
		{



		}
		if (Light* light = dynamic_cast<Light*>(component))
		{



		}
	}
}