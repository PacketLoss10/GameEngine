#include "RenderComponentManager.h"
#include "Renderer.h"

RenderComponentManager& RenderComponentManager::instance()
{
	static RenderComponentManager instance;
	return instance;
}

void RenderComponentManager::update()
{
	delete_components();

	for (RenderComponent* component : components)
	{
		if (Sprite* sprite = dynamic_cast<Sprite*>(component))
		{
			RENDERER.push(sprite);
		}
		if (Light* light = dynamic_cast<Light*>(component))
		{
			RENDERER.push(light);
		}
	}
}