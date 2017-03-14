#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <tuple>

#include "json.hpp"
using json = nlohmann::json; // for convenience

#include "Colour.h"
#include "Serialization.h"
#include "Util.h"
#include "PlayerCityCard.h"
#include "DeckofEvents.h"
#include "EventCard.h"
#include "DeckofRoles.h"

//#pragma warning(disable : 4456)

void writeToFile(std::string currentPlayer, json content);

std::unique_ptr<Map> readMapFromFile(const std::string& fileName)
{
	json j;
	{
		std::ifstream fs { fileName };
		if (!fs)
		{
			throw std::runtime_error { "File not found!" };
		}
		fs >> j;
	}
	auto map = std::make_unique<Map>();
	std::map<City*, std::vector<std::string>> connections;
	for (const auto& jCity : j["cities"])
	{
		auto city = std::make_unique<City>(jCity["name"], colourFromAbbreviation(jCity["colour"]));
		for (const auto& connection : jCity["connections"])
		{
			connections[city.get()].push_back(connection);
		}
		if (jCity["isStartingCity"].get<bool>())
		{
			map->startingCity() = city.get();
		}
		map->addCity(std::move(city));
	}
	for (const auto& pair : connections)
	{
		auto& city = *pair.first;
		for (const auto& connection : pair.second)
		{
			city.connectTo(map->findCityByName(connection));
		}
	}

	return std::move(map);
}

void writeMapToFile(const Map& map, const std::string& fileName)
{	
	json j;
	auto& jCities = j["cities"];
	for (const auto& city : map.cities())
	{
		json jCity;
		jCity["name"] = city->name();
		for (const auto& target : city->connections())
		{
			jCity["connections"].push_back(target->name());
		}
		jCity["colour"] = colourAbbreviation(city->colour());
		jCity["isStartingCity"] = map.startingCity() == *city;
		jCities.push_back(jCity);

	}
	std::ofstream { fileName } << std::setw(4) << j;
}

std::unique_ptr<GameState> readGameFromFile(const std::string & fileName)
{
	
	
	std::ifstream fs{ fileName };
	if (!fs)
	{
		throw std::runtime_error{ "File not found!" };
	}

	// parse the file as a JSON object
	json j;
	fs >> j;

	std::unique_ptr<GameState> gameState = std::make_unique<GameState>();

	// read and store the map information
	std::string mapFilePath = j["map"].get<std::string>();
	gameState->setMap(readMapFromFile(mapFilePath));

	auto& cities = gameState->map().cities();
	auto events = std::make_unique<DeckofEvents>()->deckOfEvents();
	auto roles = std::make_unique<DeckofRoles>()->roleCards();

	// PLAYER INITIALIZATION:
	std::vector<json> playerListJSON = j["players"];

	for (int i=0; i < playerListJSON.size(); i++) {
		auto playerJSON = playerListJSON.at(i);
		std::unique_ptr<Player> player = std::make_unique<Player>();

		// parse and set the player's name
		std::string playerName = playerJSON["name"].get<std::string>();
		player->setName(playerName);

		// parse and set the player's position
		std::string cityName = playerJSON["position"].get<std::string>();
		
		 //loop through cities, and find the reference to the city that matches the name
		for (auto it = cities.begin(); it != cities.end(); ++it) {
			if ((*it)->name() == cityName) {
				// found a match
				player->pawn().setPosition(**it);
			}
		}

		// parse and set the player's role
		std::string roleName = playerJSON["role"].get<std::string>();
		//search through role cards and find a match, then set the role
		auto itr = roles.begin();
		while (itr != roles.end())
		{
			if ((*itr)->name() == roleName)
			{
				player->setRole(std::move(*itr));
				itr = roles.erase(itr);
			}
			else
			{
				++itr;
			}
		}

		// loop through all of the cards in the hand list
		std::vector<json> playerHandJSON = playerJSON["hand"];
		for (int k = 0; k < playerHandJSON.size(); k++) {
			// parse and set the player's hand (of PlayerCards)
			std::string cardName = playerHandJSON.at(k).get<std::string>();

			// loop through cities, and find the cities that matches the name
			for (auto it = cities.begin(); it != cities.end(); ++it) {
				if ((*it)->name() == cardName) {
					player->addCard(std::make_unique<PlayerCityCard>((**it)));
				}
			}
			
			// loop through event cards, find the one that matches
			auto it = events.begin();
			while (it != events.end())
			{
				if ((*it)->name() == cardName)
				{
					player->addCard(std::move(*it));
					it = events.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		//std::cout << "\n" << player->getName() << "\nPosition: " << player->pawn().position().name();
		//player->displayCards();

		// store this player into the gameState
		gameState->addPlayer(std::move(player));
	}
	
	// CITIES INITIALIZATION:
	std::vector<json> cityListJSON = j["cities"];

	for (int i = 0; i < cityListJSON.size(); i++) {
		auto cityJSON = cityListJSON.at(i);

		auto cityName = cityJSON["name"].get<std::string>();
		bool isResearchStation = cityJSON["researchStation"].get<bool>();

		json disease = cityJSON["diseaseCubes"];
		int numOfBlue = disease["B"].get<int>();
		int numOfYellow = disease["Y"].get<int>();
		int numOfRed = disease["R"].get<int>();
		int numOfBlack = disease["K"].get<int>();

		for (auto it = cities.begin(); it != cities.end(); ++it) {
			if ((*it)->name() == cityName) {
				// found a match
				if (isResearchStation) {
					// mark the city as a research station
					(*it)->giveResearchStation(*gameState);
				}
				// set the disease cubes for the city
				(*it)->setDiseaseCubes(Colour::Blue, numOfBlue);
				(*it)->setDiseaseCubes(Colour::Yellow, numOfYellow);
				(*it)->setDiseaseCubes(Colour::Red, numOfRed);
				(*it)->setDiseaseCubes(Colour::Black, numOfBlack);
			}
		}
	}
	
	// INFECTION CARDS INITIALIZATION:
	json infection = j["infection"];
	auto infectionDeck = infection["deck"].get<std::vector<std::string>>();

	for (auto it = infectionDeck.begin(); it != infectionDeck.end(); ++it) {
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			// if the city names match, create an infection card and add it to the deck
			if ((*itr)->name() == *it) { 
				// TODO: does this preserve the order?
				gameState->infectionDeck().addToDeck(std::make_unique<InfectionCard>(**itr));
			}
		}
	}

	auto infectionDiscardDeck = infection["discard"].get<std::vector<std::string>>();

	for (auto it = infectionDiscardDeck.begin(); it != infectionDiscardDeck.end(); ++it) {
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			// if the city names match, create an infection card and add it to the DISCARD deck
			if ((*itr)->name() == *it) {
				// TODO: does this preserve the order?
				gameState->infectionDeck().addToDiscard(std::make_unique<InfectionCard>(**itr));
			}
		}
	}

	auto outbreakMarker = infection["outbreak"].get<int>();
	for (int k = 0; k < outbreakMarker; k++) {
		gameState->advanceOutbreakCounter();
	}

	auto infectionRateIndex = infection["rate"].get<int>();
	for (int k = 0; k <= infectionRateIndex; k++) {
		gameState->advanceInfectionCounter();
	}

	auto curedDiseasesList = infection["cured"].get<std::vector<std::string>>();
	for (auto it = curedDiseasesList.begin(); it != curedDiseasesList.end(); ++it) {
		gameState->cureDisease(colourFromAbbreviation(*it));

		// loop through all cities, and get the total cubes on the board for this disease
		size_t totalCubes = 0;
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			totalCubes += (*itr)->diseaseCubes(colourFromAbbreviation(*it));
		}
		if (totalCubes == 0) {
			// mark this disease as erradicated
			gameState->isEradicated(colourFromAbbreviation(*it));
		}
	}


	// PLAYER CARDS INITIALIZATION:

	json playerCards = j["playercards"];

	std::vector<std::string> playerCardDeck = playerCards["deck"].get<std::vector<std::string>>();
	for (auto it = playerCardDeck.begin(); it != playerCardDeck.end(); ++it) {

		// loop through cities, and find the cities that matches the name
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			if ((*itr)->name() == *it) {
				// TODO: does this preserve the order?
				gameState->playerDeck().addToDeck(std::make_unique<PlayerCityCard>((**itr)));
			}
		}

		// loop through event cards, find the one that matches
		auto itr = events.begin();
		while (itr != events.end())
		{
			if ((*itr)->name() == *it)
			{
				gameState->playerDeck().addToDeck(std::move(*itr));
				itr = events.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}

	std::vector<std::string> playerCardDiscard = playerCards["discard"].get<std::vector<std::string>>();
	for (auto it = playerCardDiscard.begin(); it != playerCardDiscard.end(); ++it) {

		// loop through cities, and find the cities that matches the name
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			if ((*itr)->name() == *it) {
				// TODO: does this preserve the order?
				gameState->playerDeck().addToDiscard(std::make_unique<PlayerCityCard>((**itr)));
			}
		}

		// loop through event cards, find the one that matches
		auto itr = events.begin();
		while (itr != events.end())
		{
			if ((*itr)->name() == *it)
			{
				gameState->playerDeck().addToDiscard(std::move(*itr));
				itr = events.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}

	return gameState;
}

void saveGame(GameState& game, const std::string& fileName)
{
	json j;
	std::ofstream os { fileName };
	j["map"] = game.map().name();
	const auto& players = game.players();
	
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
	j["players"] = playersJSON;

	const auto& cities = game.map().cities();
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
	j["cities"] = citiesJSON;

	std::vector<std::string> deckNames;
	for (const auto& card : game.playerDeck().drawPile())
	{
		deckNames.push_back(card->name());
	}
	j["playercards"]["deck"] = deckNames;

	std::vector<std::string> discardNames;
	for (const auto& card : game.playerDeck().discardPile())
	{
		discardNames.push_back(card->name());
	}
	j["playercards"]["discard"] = discardNames;

	std::vector<std::string> infDeckNames;
	for (const auto& card : game.infectionDeck().drawPile())
	{
		infDeckNames.push_back(card->name());
	}
	j["infection"]["deck"] = infDeckNames;

	std::vector<std::string> infDiscNames;
	for (const auto& card : game.infectionDeck().discardPile())
	{
		infDiscNames.push_back(card->name());
	}
	j["infection"]["discard"] = infDiscNames;

	j["infection"]["outbreak"] = game.outbreakCounter();
	j["infection"]["rate"] = game.infectionCounter();

	bool hasCured = false;
	for (const auto& colour : colours())
	{
		if (game.isCured(colour))
		{
			hasCured = true;
			j["infection"]["cured"].push_back(colourAbbreviation(colour));
		}
	}
	if (!hasCured) 
	{
		j["infection"]["cured"] = json::array();
	}

	os << std::setw(4) << j;
}

void writeToFile(std::string currentPlayer, json content)
{
	std::string saveFileName = currentPlayer + "_save.json";
	std::ofstream fs{ saveFileName };
	if (!fs)
	{
		throw std::runtime_error{ "File I/O error!" };
	}

	fs << content;
}