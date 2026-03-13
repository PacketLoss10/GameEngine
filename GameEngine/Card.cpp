#include "Card.h"
#include "InputHandler.h"
#include "TickClock.h"

Card::Card()
{
	sprite = new Sprite(this);
	sprite->set_texture(Texture("ugin-eye-of-the-storms.png"));
	sprite->set_rect(TextureRect(IVector(0, 0), IVector(672, 936)));
	sprite->set_lit(false);
	sprite->finalise();

	collision = new BoxCollisionComponent(this);
	collision->set_size(Vector2(672.f, 936.f));
	collision->set_relativePosition(Vector2(336.f, 468.f));
	collision->on_mouse_begin_overlap.bind(this, &Card::mouse_overlap_begin);
	collision->on_mouse_end_overlap.bind(this, &Card::mouse_overlap_end);
	collision->on_begin_overlap.bind(this, &Card::overlap_begin); 
	collision->on_end_overlap.bind(this, &Card::overlap_end);
	collision->finalise();

	set_scale(Vector2(0.5f, 0.5f));
}

void Card::update_tick()
{
}

void Card::input_tick()
{
	if (INPUT.is_button_pressed(Mouse::M1) && collision->is_mouseOverlapping())
	{
		rotate_by(3.14f / 2.f);
	}

	if (INPUT.is_key_held(Keyboard::W))
	{
		move_by(Vector2(0.f, -100.f) * DELTA_TIME);
	}
	if (INPUT.is_key_held(Keyboard::A))
	{
		move_by(Vector2(-100.f, 0.f) * DELTA_TIME);
	}
	if (INPUT.is_key_held(Keyboard::S))
	{
		move_by(Vector2(0.f, 100.f) * DELTA_TIME);
	}
	if (INPUT.is_key_held(Keyboard::D))
	{
		move_by(Vector2(100.f, 0.f) * DELTA_TIME);
	}
}

void Card::mouse_overlap_begin(Entity*, CollisionComponent*, const Vector2&)
{
	std::cout << "begin overlap with mouse" << std::endl;
}

void Card::mouse_overlap_end(Entity*, CollisionComponent*, const Vector2&)
{
	std::cout << "end overlap with mouse" << std::endl;
}

void Card::overlap_begin(Entity*, CollisionComponent*, Entity*, CollisionComponent*)
{
	std::cout << "begin overlap" << std::endl;
}

void Card::overlap_end(Entity*, CollisionComponent*, Entity*, CollisionComponent*)
{
	std::cout << "end overlap" << std::endl;
}
