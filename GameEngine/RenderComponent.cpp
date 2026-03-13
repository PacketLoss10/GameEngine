#include "RenderComponent.h"
#include "RenderComponentManager.h"

RenderComponent::RenderComponent(Entity* owner) :Component(owner) {}

void RenderComponent::finalise()
{
	RENDER_COMPONENT_MANAGER.register_component(this);
}
