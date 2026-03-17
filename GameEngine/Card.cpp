#include "Card.h"
#include "InputHandler.h"
#include "TickClock.h"

Card::Card()
{
	sprite = new Sprite(this);
	sprite->set_texture(Texture("ugin-eye-of-the-storms.png"));
	sprite->set_texture(Texture("back-of-card.png"));
	sprite->set_rect(TextureRect(IVector(0, 0), IVector(672, 936)));
	sprite->set_lit(false);
	sprite->set_relativePosition(Vector2(-336.f, -468.f));
	sprite->finalise();

	collision = new BoxCollisionComponent(this);
	collision->set_size(Vector2(672.f, 936.f));
	collision->on_overlap.bind(this, &Card::overlap);
	collision->on_mouse_begin_overlap.bind(this, &Card::mouse_overlap_begin);
	collision->on_mouse_end_overlap.bind(this, &Card::mouse_overlap_end);
	collision->on_begin_overlap.bind(this, &Card::overlap_begin); 
	collision->on_end_overlap.bind(this, &Card::overlap_end);
	collision->finalise();

	set_scale(Vector2(0.25f, 0.25f));
}

Card::~Card()
{
	delete sprite;
	delete collision;
}

void Card::update_tick()
{
}

void Card::input_tick()
{
	if (INPUT.is_button_held(Mouse::M1))
	{
		if (collision->is_mouseOverlapping())
		{
			if (!grabbed)
			{
				grabbed = true;
				grabbedAt = INPUT.get_mouse_pos() - get_position();
			}
			set_position(INPUT.get_mouse_pos() - grabbedAt);
		}
	}
	else grabbed = false;

	if (INPUT.is_button_pressed(Mouse::M2)&&collision->is_mouseOverlapping())
	{
		tapped ? untap() : tap();
	}
}

void Card::tap()
{
	tapped = true;
	set_forward(Vector2(0.f, -1.f));
}

void Card::untap()
{
	tapped = false;
	set_forward(Vector2(1.f, 0.f));
}

void Card::mouse_overlap_begin(Entity*, CollisionComponent*, const Vector2&)
{
	std::cout << "begin overlap with mouse" << std::endl;
}

void Card::mouse_overlap_end(Entity*, CollisionComponent*, const Vector2&)
{
	std::cout << "end overlap with mouse" << std::endl;
}

void Card::overlap(Entity*, CollisionComponent*, Entity*, CollisionComponent*)
{
}

void Card::overlap_begin(Entity*, CollisionComponent*, Entity*, CollisionComponent*)
{
	std::cout << "begin overlap" << std::endl;
}

void Card::overlap_end(Entity*, CollisionComponent*, Entity*, CollisionComponent*)
{
	std::cout << "end overlap" << std::endl;
}
