#include "CircleCollisionComponent.h"
#include "CollisionComponentManager.h"
#include "GameWindow.h"

CircleCollisionComponent::CircleCollisionComponent(Entity* owner, bool enabled, Transform transform, FVector radius) :CollisionComponent(owner, enabled, transform), radius(radius) {}

void CircleCollisionComponent::init()
{
	COLLISION_COMPONENT_MANAGER.register_component(this);
}

void CircleCollisionComponent::render()
{
	sf::CircleShape circle;

	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(0.05f);
	circle.setOutlineColor(sf::Color::White);
	circle.setRadius(1.f);
	circle.setOrigin(FVector(1.f, 1.f));
	circle.setPosition(transform.position);
	circle.setScale(radius.component_wise_mult(transform.scale));
	circle.setRotation(sf::radians(transform.forward.angle()));

	GAME_WINDOW.render(circle, nullptr);
}

const FVector& CircleCollisionComponent::get_radius() const
{
	return radius;
}

void CircleCollisionComponent::set_radius(const FVector& radius)
{
	this->radius = radius;
}