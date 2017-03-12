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

#pragma warning(disable : 4456)

std::unique_ptr<Map> readMapFromFile(const std::string& fileName)
{
	std::ifstream fs { fileName };
	if (!fs)
	{
		throw std::runtime_error { "File not found!" };
	}

	std::unique_ptr<Map> map;
	std::map<City*, std::vector<std::string>> connections;

	{
		std::vector<std::unique_ptr<City>> cities;
		City* startingCity;
		while (!fs.eof())
		{
			auto line = getline(fs);
			if (line.empty() || line[0] == '\\')
			{
				continue;
			}
			else if (line[0] == '\t')
			{
				connections[cities.back().get()].push_back(line.substr(1));
			}
			else
			{
				bool isStartingCity = false;
				if (line[0] == '*')
				{
					line = line.substr(1);
					isStartingCity = true;
				}
				std::string name, colour;
				std::tie(name, colour) = splitOnLastSpace(line);
				cities.push_back(std::make_unique<City>(name, colourFromAbbreviation(colour)));
				connections[cities.back().get()];
				if (isStartingCity)
				{
					startingCity = cities.back().get();
				}
			}
		}

		map = std::make_unique<Map>(fileName, startingCity, std::move(cities));
	}

	for (const auto& list : connections)
	{
		for (const auto& targetName : list.second)
		{
			auto& target = map->findCityByName(targetName);
			list.first->connectTo(target);
		}
	}

	return std::move(map);
}

/*
void writeMapToFile(const Map& map, const std::string& fileName)
{
	//throw std::logic_error { "Not implemented." };
	std::map<std::string, std::string> players;
	for (const auto& player : map.players())
	{
		players[player->name()] = player->pawn().position().name();
	}

	std::map<std::string, std::pair<std::string, std::vector<std::string>>> cities;
	for (const auto& source : map.cities())
	{
		const auto& connections = source->connections();
		cities[source->name()].first = colourName(source->colour());
		for (const auto& target : connections)
		{
			cities[source->name()].second.push_back(target->name());
		}
	}
	
	std::ofstream stream{ fileName };
	stream << "// Players - format\n// name:\n// @location\n";
	for (const auto& pair : players)
	{
		stream << pair.first << ":\n@" << pair.second << "\n";
	}

	stream << "\n";

	stream << "// Cities and connections - format\n// name colour\n//     target connection\n";
	for (const auto& pair : cities)
	{
		stream << pair.first << " " << pair.second.first << "\n";
		for (const auto& target : pair.second.second)
		{
			stream << "\t" << target << "\n";
		}
	}
}
*/

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
		auto totalCubes = 0;
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