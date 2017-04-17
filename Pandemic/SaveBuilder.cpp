#include <fstream>
#include "SaveBuilder.h"
#include "Board.h"

void SaveBuilder::persist(const std::string& fileName)
{
	std::ofstream os{ fileName };
	os << std::setw(4) << gameFile;
}

SaveBuilder& SaveBuilder::saveMap()
{
	auto name = Board::instance().map().name();
	gameFile["map"] = name;

	return *this;
}

SaveBuilder& SaveBuilder::savePlayers()
{
	const auto& players = Board::instance().players();

	std::vector<json> playersJSON(players.size());
	for (size_t idx = 0; idx < players.size(); ++idx)
	{
		auto& pj = playersJSON[idx];
		auto& player = players[idx];
		pj["name"] = player->name();
		pj["position"] = player->pawn().position().name();
		pj["role"] = player->role().name();
		std::vector<std::string> cardNames;
		for (const auto& card : player->cards())
		{
			pj["hand"].push_back(card->name());
		}
	}
	gameFile["players"] = playersJSON;
	
	return *this;
}

SaveBuilder& SaveBuilder::saveCities()
{
	const auto& cities = Board::instance().map().cityView();
	std::vector<json> citiesJSON(cities.size());
	for (size_t idx = 0; idx < cities.size(); ++idx)
	{
		auto& cj = citiesJSON[idx];
		auto& city = cities[idx];
		cj["name"] = city->name();
		cj["colour"] = colourAbbreviation(city->colour());
		std::map<std::string, size_t> cubes;
		for (const auto& colour : colours())
		{
			cubes[colourAbbreviation(colour)] = city->diseaseCubes(colour);
		}
		cj["diseaseCubes"] = cubes;
		cj["researchStation"] = city->hasResearchStation();
	}
	gameFile["cities"] = citiesJSON;
	
	return *this;
}

SaveBuilder& SaveBuilder::savePlayerCards()
{
	std::vector<std::string> deckNames;
	for (const auto& card : Board::instance().playerDeck().drawPile())
	{
		deckNames.push_back(card->name());
	}
	gameFile["playercards"]["deck"] = deckNames;

	std::vector<std::string> discardNames;
	for (const auto& card : Board::instance().playerDeck().discardPile())
	{
		discardNames.push_back(card->name());
	}
	gameFile["playercards"]["discard"] = discardNames;
	
	return *this;
}

SaveBuilder& SaveBuilder::saveInfectionCards()
{
	std::vector<std::string> infDeckNames;
	for (const auto& card : Board::instance().infectionDeck().drawPile())
	{
		infDeckNames.push_back(card->name());
	}
	gameFile["infection"]["deck"] = infDeckNames;

	std::vector<std::string> infDiscNames;
	for (const auto& card : Board::instance().infectionDeck().discardPile())
	{
		infDiscNames.push_back(card->name());
	}
	gameFile["infection"]["discard"] = infDiscNames;

	gameFile["infection"]["outbreak"] = Board::instance().outbreaks();
	gameFile["infection"]["rate"] = Board::instance().infectionCounter();

	bool hasCured = false;
	gameFile["infection"];
	for (const auto& colour : colours())
	{
		if (Board::instance().isCured(colour))
		{
			hasCured = true;
			gameFile["infection"]["cured"].push_back(colourAbbreviation(colour));
		}
	}
	if (!hasCured)
	{
		gameFile["infection"]["cured"] = json::array();
	}

	return *this;
}
