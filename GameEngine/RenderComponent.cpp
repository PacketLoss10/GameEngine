#include "RenderComponent.h"

RenderComponent::RenderComponent(Entity* owner, bool enabled, Transform transform) :Component(owner, enabled), RenderObject(transform) {}