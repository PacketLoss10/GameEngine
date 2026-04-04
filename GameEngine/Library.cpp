#include "Library.h"
#include "Card.h"
#include "SpriteComponent.h"
#include "BoxCollisionComponent.h"
#include "PrimitiveBoxComponent.h"
#include "TextComponent.h"
#include "DragDropComponent.h"
#include "InputHandler.h"
#include "World.h"

Library::Library()
{
	sprite = new SpriteComponent(this);
	sprite->set_texture(Texture("Cards//back-of-card.png"));
	sprite->set_rect(TextureRect(IntVector(0, 0), IntVector(672, 936)));
	sprite->set_relativePosition(Vector2(-336.f, -468.f));

	collision = new BoxCollisionComponent(this);
	collision->set_size(Vector2(672.f, 936.f));

	outline = new PrimitiveBoxComponent(this);
	outline->set_size(Vector2(672.f, 936.f));
	outline->set_fillColor(Color(0, 0, 0, 0));
	outline->set_outlineColor(Color(255, 255, 255, 255));
	outline->set_outlineThickness(5.f);
	outline->set_relativePosition(Vector2(-336.f, -468.f));

	label = new TextComponent(this);
	label->set_text("Library");
	label->set_fontFilepath("font.ttf");
	label->set_characterSize(100);
	label->set_fillColor(Color(255, 255, 255, 255));
	label->set_outlineThickness(0.f);
	label->set_zOrder(-1);
	label->set_relativePosition(Vector2(-156.f, -463.f));

	dragDrop = new DragDropComponent(this);
	dragDrop->set_geometry(collision);
	dragDrop->set_draggable(false);
	dragDrop->set_layer(-1);
	dragDrop->on_hover_begin.bind(this, &Library::mouse_hover);
	dragDrop->on_hover_end.bind(this, &Library::mouse_unhover);
	dragDrop->on_drag_begin.bind(this, &Library::drag_begin);

	set_scale(Vector2(0.3f, 0.3f));

	for (int i = 0; i < 5; i++)
	{
		cards.push_back(new Card("ugin-eye-of-the-storms"));
		cards.back()->set_position(get_position());
	}
}

Library::~Library()
{
	delete sprite;
	delete collision;
	delete outline;
	delete dragDrop;
	delete label;
	for (Card* card : cards)
	{
		card->despawn();
		delete card;
	}
}

Card* Library::draw_card()
{
	if (cards.empty())
		return nullptr;

	Card* card = cards.back();
	WORLD.spawn_entity(card);
	cards.pop_back();

	if (cards.empty())
		sprite->set_enabled(false);

	return card;
}

void Library::place_card(Card* card)
{
	cards.push_back(card);

	if (!cards.empty())
		sprite->set_enabled(true);
}

void Library::mouse_hover()
{
	set_scale(Vector2(0.35f, 0.35f));
}

void Library::mouse_unhover()
{
	set_scale(Vector2(0.3f, 0.3f));
}

void Library::drag_begin(const Vector2&)
{
	if (cards.empty())
		return;

	draw_card()->get_dragDrop()->drag_this();
}

SpriteComponent* Library::get_sprite() const
{
	return sprite;
}

BoxCollisionComponent* Library::get_collision() const
{
	return collision;
}

PrimitiveBoxComponent* Library::get_outline() const
{
	return outline;
}

TextComponent* Library::get_label() const
{
	return label;
}

DragDropComponent* Library::get_dragDrop() const
{
	return dragDrop;
}