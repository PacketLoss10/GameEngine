#include "RenderComponentManager.h"
#include "SpriteComponent.h"
#include "LightComponent.h"
#include "PrimitiveBoxComponent.h"
#include "PrimitiveCircleComponent.h"
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
		else if (PrimitiveBoxComponent* box = dynamic_cast<PrimitiveBoxComponent*>(component))
		{
			RENDERER.push(box->build_render_data());
		}
		else if (PrimitiveCircleComponent* circle = dynamic_cast<PrimitiveCircleComponent*>(component))
		{
			RENDERER.push(circle->build_render_data());
		}
	}
}