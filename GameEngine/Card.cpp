#include "Card.h"
#include "InputHandler.h"
#include "TickClock.h"

Card::Card()
{
	sprite = new Sprite(this, true, Texture("ugin-eye-of-the-storms.png"), TextureRect(IVector(0, 0), IVector(672, 936)), 0, Transform());
	sprite->set_lit(false);
	sprite->init();

	collision = new BoxCollisionComponent(this, true, Transform(), FVector(672.f, 936.f));
	collision->on_begin_overlap.bind(this, &Card::begin);
	collision->on_end_overlap.bind(this, &Card::end);
	collision->init();
}

void Card::update_tick()
{
	sprite->set_transform(transform);
	collision->set_transform(transform);
}

void Card::input_tick()
{
	if (INPUT.is_key_held(Keyboard::W))
	{
		move_by(FVector(0.f, -100.f) * DELTA_TIME);
	}
	if (INPUT.is_key_held(Keyboard::A))
	{
		move_by(FVector(-100.f, 0.f) * DELTA_TIME);
	}
	if (INPUT.is_key_held(Keyboard::S))
	{
		move_by(FVector(0.f, 100.f) * DELTA_TIME);
	}
	if (INPUT.is_key_held(Keyboard::D))
	{
		move_by(FVector(100.f, 0.f) * DELTA_TIME);
	}
}

void Card::begin(Entity*, CollisionComponent*, Entity*, CollisionComponent*)
{
	std::cout << "begin overlap" << std::endl;
}

void Card::end(Entity*, CollisionComponent*, Entity*, CollisionComponent*)
{
	std::cout << "end overlap" << std::endl;
}
