#include "Transform.h"

Transform Transform::identity = Transform(Vector2(0.f, 0.f), Vector2(1.f, 0.f), Vector2(1.f, 1.f));

Transform::Transform(Vector2 position, Vector2 forward, Vector2 scale) :position(position), forward(forward), scale(scale) {}