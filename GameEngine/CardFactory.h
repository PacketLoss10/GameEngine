#pragma once

#include "Card.h"

class Library;
class CommandZone;

class CardFactory
{
private:
	std::vector<Card*> cards;
public:
	~CardFactory();

	void create_deck(const std::string& deckName, Library* library, CommandZone* commandZone);
};