#include "RenderComponent.h"
#include "RenderComponentManager.h"

RenderComponent::RenderComponent(Entity* owner) :Component(owner) {}

void RenderComponent::spawn()
{
	RENDER_COMPONENT_MANAGER.register_component(this);
}