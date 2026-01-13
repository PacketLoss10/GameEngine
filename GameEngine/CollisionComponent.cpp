#include "CollisionComponent.h"
#include "CollisionComponentManager.h"

CollisionComponent::CollisionComponent(Entity* owner, bool enabled, Transform transform) :Component(owner, enabled), Transformable(transform) {}