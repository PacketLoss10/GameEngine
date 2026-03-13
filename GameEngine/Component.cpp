#include "Component.h"
#include "Entity.h"

Component::Component(Entity* owner) :owner(owner) {}

Entity* Component::get_owner() const
{
	return owner;
}

bool Component::is_enabled() const
{
	return enabled;
}

void Component::set_enabled(bool enabled)
{
	this->enabled = enabled;
}

const Transform& Component::get_relativeTransform() const
{
	return relativeTransform;
}

void Component::set_relativeTransform(const Transform& relativeTransform)
{
	this->relativeTransform = relativeTransform;
}

const Vector2& Component::get_relativePosition() const
{
	return relativeTransform.position;
}

void Component::set_relativePosition(const Vector2& relativePosition)
{
	relativeTransform.position = relativePosition;
}

const Vector2& Component::get_relativeForward() const
{
	return relativeTransform.forward;
}

void Component::set_relativeForward(const Vector2& relativeForward)
{
	relativeTransform.forward = relativeForward;
}

float Component::get_relativeRotation() const
{
	return atan2f(relativeTransform.forward.y, relativeTransform.forward.x);
}

void Component::set_relativeRotation(float relativeRotation)
{
	relativeTransform.forward = Vector2(cosf(relativeRotation), sinf(relativeRotation));
}

const Vector2& Component::get_relativeScale() const
{
	return relativeTransform.scale;
}

void Component::set_relativeScale(const Vector2& relativeScale)
{
	relativeTransform.scale = relativeScale;
}

const Vector2& Component::get_worldPosition() const
{
	const Transform& ownerTransform = owner->get_transform();

	Vector2 scaled = relativeTransform.position.component_wise_mult(ownerTransform.scale);
	Vector2 rotated = scaled.rotated_by(ownerTransform.forward.angle());

	return ownerTransform.position + rotated;
}

void Component::set_worldPosition(const Vector2& worldPosition)
{
	const Transform& ownerTransform = owner->get_transform();

	Vector2 offset = worldPosition - ownerTransform.position;
	Vector2 right = ownerTransform.forward.perpendicular();
	Vector2 local = Vector2(offset.x * ownerTransform.forward.x + offset.y * ownerTransform.forward.y,
		offset.x * right.x + offset.y * right.y);

	relativeTransform.position = Vector2(local.x / ownerTransform.scale.x, local.y / ownerTransform.scale.y);
}

const Vector2& Component::get_worldForward() const
{
	const Transform& ownerTransform = owner->get_transform();

	return relativeTransform.forward.rotated_by(ownerTransform.forward.angle());
}

void Component::set_worldForward(const Vector2& worldForward)
{
	const Transform& ownerTransform = owner->get_transform();

	Vector2 right = ownerTransform.forward.perpendicular();
	Vector2 local = Vector2(worldForward.x * ownerTransform.forward.x + worldForward.y * ownerTransform.forward.y,
		worldForward.x * right.x + worldForward.y * right.y);

	relativeTransform.forward = local.normalised();
}

float Component::get_worldRotation() const
{
	Vector2 worldForward = get_worldForward();
	return atan2f(worldForward.y, worldForward.x);
}

void Component::set_worldRotation(float worldRotation)
{
	Vector2 worldForward = Vector2(cosf(worldRotation), sinf(worldRotation));
	set_worldForward(worldForward);
}

const Vector2& Component::get_worldScale() const
{
	const Transform& ownerTransform = owner->get_transform();

	return relativeTransform.scale.component_wise_mult(ownerTransform.scale);
}

void Component::set_worldScale(const Vector2& worldScale)
{
	const Transform& ownerTransform = owner->get_transform();

	relativeTransform.scale = worldScale.component_wise_div(ownerTransform.scale);
}