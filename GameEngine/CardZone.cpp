#include "CardZone.h"
#include "World.h"

CardZone::CardZone() :Entity()
{
	sprite = new SpriteComponent(this);
	sprite->set_texture(Texture("Assets//Sprites//Cards//back-of-card.png"));
	sprite->set_rect(TextureRect(IntVector(0, 0), IntVector(672, 936)));
	sprite->set_relativePosition(Vector2(-336.f, -468.f));
	sprite->set_enabled(false);

	area = new BoxCollisionComponent(this);
	area->set_size(Vector2(672.f, 936.f));

	outline = new PrimitiveBoxComponent(this);
	outline->set_size(Vector2(672.f, 936.f));
	outline->set_fillColor(Color(0, 0, 0, 0));
	outline->set_outlineColor(Color(255, 255, 255, 255));
	outline->set_outlineThickness(5.f);
	outline->set_relativePosition(Vector2(-336.f, -468.f));

	label = new TextComponent(this);
	label->set_text("CARD ZONE");
	label->set_fontFilepath("Assets//Fonts//font.ttf");
	label->set_characterSize(100);
	label->set_fillColor(Color(255, 255, 255, 255));
	label->set_outlineThickness(0.f);
	label->set_zOrder(-1);
	label->set_relativePosition(Vector2(0.f, -520.f));
	label->set_autoCenter(true);

	mouseInteraction = new DragDropComponent(this);
	mouseInteraction->set_geometry(area);
	mouseInteraction->set_draggable(false);
	mouseInteraction->set_layer(-1);
	mouseInteraction->on_hover_begin.bind(this, &CardZone::mouse_hover);
	mouseInteraction->on_hover_end.bind(this, &CardZone::mouse_unhover);
	mouseInteraction->on_drag_begin.bind(this, &CardZone::drag_begin);

	set_scale(Vector2(0.3f, 0.3f));
}

CardZone::~CardZone()
{
	delete area;
	delete outline;
	delete label;
	delete mouseInteraction;
}

void CardZone::add_card(Card* card)
{
	cards.push_back(card);

	sprite->set_enabled(true);
	sprite->set_texture(cards.back()->get_sprite()->get_texture());
}

Card* CardZone::remove_card()
{
	if (cards.empty())
		return nullptr;

	Card* card = cards.back();
	WORLD.spawn_entity(card);
	cards.pop_back();

	if (cards.empty())
		sprite->set_enabled(false);
	else sprite->set_texture(cards.back()->get_sprite()->get_texture());

	return card;
}

void CardZone::mouse_hover()
{
	set_scale(Vector2(0.35f, 0.35f));
}

void CardZone::mouse_unhover()
{
	set_scale(Vector2(0.3f, 0.3f));
}

void CardZone::drag_begin(const Vector2& mousePos) 
{
	if (cards.empty())
		return;

	remove_card()->get_dragDrop()->drag_this();
}

BoxCollisionComponent* CardZone::get_area() const
{
	return area;
}

PrimitiveBoxComponent* CardZone::get_outline() const
{
	return outline;
}

TextComponent* CardZone::get_label() const
{
	return label;
}

DragDropComponent* CardZone::get_mouseInteraction() const
{
	return mouseInteraction;
}