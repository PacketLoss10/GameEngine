#pragma once

#include "CardZone.h"

enum class LibraryPosition
{
	Top, Bottom
};

class Library :public CardZone
{
public:
	Library();
	~Library();

	void input_tick() override;

	void add_card(Card* card) override;
	Card* remove_card() override;

	void shuffle();
};