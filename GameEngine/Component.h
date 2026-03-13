#pragma once

#include "Transform.h"

class Entity;

class Component
{
protected:
	Entity* owner = nullptr;
	bool enabled = true;
	Transform relativeTransform = Transform::identity;
	Transform origin;
public:
	Component(Entity* owner);
	virtual ~Component() = default;

	virtual void finalise() {};
	virtual void tick() {};
	virtual void render() {};

	Entity* get_owner() const;

	bool is_enabled() const;
	void set_enabled(bool enabled);

	const Transform& get_relativeTransform() const;
	void set_relativeTransform(const Transform& relativeTransform);

	const Vector2& get_relativePosition() const;
	void set_relativePosition(const Vector2& relativePosition);

	const Vector2& get_relativeForward() const;
	void set_relativeForward(const Vector2& relativeForward);

	float get_relativeRotation() const;
	void set_relativeRotation(float relativeRotation);

	const Vector2& get_relativeScale() const;
	void set_relativeScale(const Vector2& relativeScale);

	const Vector2& get_worldPosition() const;
	void set_worldPosition(const Vector2& worldPosition);

	const Vector2& get_worldForward() const;
	void set_worldForward(const Vector2& worldForward);

	float get_worldRotation() const;
	void set_worldRotation(float worldRotation);

	const Vector2& get_worldScale() const;
	void set_worldScale(const Vector2& worldScale);
};