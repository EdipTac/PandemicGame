#include "BoardBuilder.h"
#include "PlayerCityCard.h"
#include "DeckofRoles.h"
#include "DeckOfEvents.h"
#include "Map.h"
#include "Board.h"
#include <fstream>


std::unique_ptr<Map> readMapFromFile(const std::string& fileName)
{
	json j;
	{
		std::ifstream fs{ fileName };
		if (!fs)
		{
			throw std::runtime_error{ "File not found!" };
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
	std::ofstream{ fileName } << std::setw(4) << j;
}

BoardBuilder& BoardBuilder::loadBoard(std::string& gameSaveFile)
{
	std::ifstream fs{ gameSaveFile };
	if (!fs)
	{
		throw std::runtime_error{ "File not found!" };
	}

	// parse the file as a JSON object
	json j;
	fs >> j;

	gameFile = j;

	const auto mapFile = gameFile["map"].get<std::string>();
	Board::instance().setMap(std::move(readMapFromFile(mapFile)));

	return *this;
}

BoardBuilder& BoardBuilder::loadPlayers()
{
	auto& cities = Board::instance().map().cities();
	auto events = event::cards();
	DeckOfRoles deckOfRoles;
	std::vector<std::unique_ptr<RoleCard>> roles;
	while (!deckOfRoles.empty())
	{
		roles.push_back(deckOfRoles.drawTopCard());
	}


	// PLAYER INITIALIZATION:
	std::vector<json> playerListJSON = this->gameFile["players"];

	for (int i = 0; i < playerListJSON.size(); i++) {
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
				player->moveTo(**it);
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

		// store this player into the gameState
		Board::instance().addPlayer(std::move(player));
	}

	return *this;
	}
	
BoardBuilder& BoardBuilder::loadCities()
{
	auto& cities = Board::instance().map().cities();

	// CITIES INITIALIZATION:
	std::vector<json> cityListJSON = gameFile["cities"];

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
					(*it)->giveResearchStation(Board::instance());
				}
				// set the disease cubes for the city
				(*it)->setDiseaseCubes(Colour::Blue, numOfBlue);
				(*it)->setDiseaseCubes(Colour::Yellow, numOfYellow);
				(*it)->setDiseaseCubes(Colour::Red, numOfRed);
				(*it)->setDiseaseCubes(Colour::Black, numOfBlack);
			}
		}
	}

	return *this;
	}
	
BoardBuilder& BoardBuilder::loadInfectionCards()
{
	auto& cities = Board::instance().map().cities();

	// INFECTION CARDS INITIALIZATION:
	json infection = gameFile["infection"];
	auto infectionDeck = infection["deck"].get<std::vector<std::string>>();

	for (auto it = infectionDeck.begin(); it != infectionDeck.end(); ++it) {
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			// if the city names match, create an infection card and add it to the deck
			if ((*itr)->name() == *it) { 
				Board::instance().infectionDeck().addToDeck(std::make_unique<InfectionCard>(**itr));
			}
		}
	}

	auto infectionDiscardDeck = infection["discard"].get<std::vector<std::string>>();

	for (auto it = infectionDiscardDeck.begin(); it != infectionDiscardDeck.end(); ++it) {
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			// if the city names match, create an infection card and add it to the DISCARD deck
			if ((*itr)->name() == *it) {
				Board::instance().infectionDeck().addToDiscard(std::make_unique<InfectionCard>(**itr));
			}
		}
	}

	auto outbreakMarker = infection["outbreak"].get<int>();
	for (int k = 0; k < outbreakMarker; k++) {
		Board::instance().advanceOutbreakCounter();
	}

	auto infectionRateIndex = infection["rate"].get<int>();
	for (int k = 0; k <= infectionRateIndex; k++) {
		Board::instance().advanceInfectionCounter();
	}

	auto curedDiseasesList = infection["cured"].get<std::vector<std::string>>();
	for (auto it = curedDiseasesList.begin(); it != curedDiseasesList.end(); ++it) {
		Board::instance().cureDisease(colourFromAbbreviation(*it));

		// loop through all cities, and get the total cubes on the board for this disease
		size_t totalCubes = 0;
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			totalCubes += (*itr)->diseaseCubes(colourFromAbbreviation(*it));
		}
		if (totalCubes == 0) {
			// mark this disease as erradicated
			Board::instance().isEradicated(colourFromAbbreviation(*it));
		}
	}

	return *this;
}

BoardBuilder& BoardBuilder::loadPlayerCards()
{
	auto& cities = Board::instance().map().cities();
	auto events = event::cards();
	
	// PLAYER CARDS INITIALIZATION:
	json playerCards = gameFile["playercards"];

	std::vector<std::string> playerCardDeck = playerCards["deck"].get<std::vector<std::string>>();
	for (auto it = playerCardDeck.begin(); it != playerCardDeck.end(); ++it) {

		// loop through cities, and find the cities that matches the name
		for (auto itr = cities.begin(); itr != cities.end(); ++itr) {
			if ((*itr)->name() == *it) {
				Board::instance().playerDeck().addToDeck(std::make_unique<PlayerCityCard>((**itr)));
			}
		}

		// loop through event cards, find the one that matches
		auto itr = events.begin();
		while (itr != events.end())
		{
			if ((*itr)->name() == *it)
			{
				Board::instance().playerDeck().addToDeck(std::move(*itr));
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
				Board::instance().playerDeck().addToDiscard(std::make_unique<PlayerCityCard>((**itr)));
			}
		}

		// loop through event cards, find the one that matches
		auto itr = events.begin();
		while (itr != events.end())
		{
			if ((*itr)->name() == *it)
			{
				Board::instance().playerDeck().addToDiscard(std::move(*itr));
				itr = events.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}

	return *this;
}
