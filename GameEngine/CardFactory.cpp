#include "CardFactory.h"
#include "Library.h"
#include "CommandZone.h"
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

CardFactory::~CardFactory()
{
	for (Card* card : cards)
	{
		delete card;
	}
}

void CardFactory::create_deck(const std::string& deckName, Library* library, CommandZone* commandZone)
{
	if (!library || !commandZone)
	{
		std::cerr << "Library or CommandZone was null" << std::endl;
		return;
	}

	if (!std::filesystem::exists("Assets//Data//Decks//" + deckName + ".json"))
	{
		std::cerr << "Failed to load deck: " << deckName << std::endl;
		return;
	}

	std::ifstream file("Assets//Data//Decks//" + deckName + ".json");
	nlohmann::json data = nlohmann::json::parse(file);

	for (auto entry = data["cards"].begin(); entry < data["cards"].end() - 1; entry++)
	{
		for (int i = 0; i < (*entry)["count"]; i++)
		{
			Card* card = new Card((*entry)["front"].get<std::string>(), (*entry)["back"].get<std::string>());
			cards.push_back(std::move(card));
			library->add_card(card);
		}
	}

	Card* card = new Card(data["cards"].back()["front"].get<std::string>(), data["cards"].back()["back"].get<std::string>());
	cards.push_back(std::move(card));
	commandZone->add_card(card);
}