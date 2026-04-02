#include "RenderComponentManager.h"
#include "SpriteComponent.h"
#include "LightComponent.h"
#include "Renderer.h"

RenderComponentManager& RenderComponentManager::instance()
{
	static RenderComponentManager instance;
	return instance;
}
#include <iostream>
void RenderComponentManager::update()
{
	delete_components();

	for (RenderComponent* component : components)
	{
		if(!component->is_enabled())
			continue;

		if (SpriteComponent* sprite = dynamic_cast<SpriteComponent*>(component))
		{
			RENDERER.push(sprite->build_render_data());
		}
		else if(LightComponent* light = dynamic_cast<LightComponent*>(component))
		{
			RENDERER.push(light->build_render_data());
		}
	}
}