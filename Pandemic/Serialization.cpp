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

void readGameFromFile(const std::string & fileName)
{
	
	
	std::ifstream fs{ fileName };
	if (!fs)
	{
		throw std::runtime_error{ "File not found!" };
	}

	// parse the file as a JSON object
	json j;
	fs >> j;

	std::unique_ptr<GameState> gameState;

	// read and store the map information
	std::string mapFilePath = j["map"].get<std::string>();
	//gameState->setMap(readMapFromFile(mapFilePath)); // causing some memory error...


	// PLAYER INITIALIZATION:
	std::vector<json> playerListJSON = j["players"];

	for (int i=0; i < playerListJSON.size(); i++) {
		//std::cout << playerListJSON.at(i)["name"].get<std::string>() << "\n";
		auto playerJSON = playerListJSON.at(i);
		std::unique_ptr<Player> player;

		// parse and set the player's name
		std::string playerName = playerJSON["name"].get<std::string>();
		//player->setName(playerName); // causing a error for some reason...

		// parse and set the player's position
		std::string cityName = playerJSON["position"].get<std::string>();
		//player->pawn().setPosition(std::make_unique<City>(cityName, "color"));

		// parse and set the player's role
		std::string roleName = playerJSON["role"].get<std::string>();
		//player->setRole(std::make_unique<RoleCard>(roleName, "description", "color"));

		// loop through all of the cards in the hand list
		std::vector<json> playerHandJSON = playerJSON["hand"];
		for (int j = 0; j < playerHandJSON.size(); j++) {
			// parse and set the player's hand (of PlayerCards)
			std::string cardName = playerHandJSON.at(j).get<std::string>();

			// some way of determining if it is a Event or a City card?
			/*
			if (EventCard) {
				player->addCard(std::make_unique<EventCard>());
			}
			else if (PlayerCityCard) {
				player->addCard(std::make_unique<PlayerCityCard>());
			}
			*/
		}



		// store this player into the gameState
		// also set current/next player?
		//gameState->addPlayer(std::move(player));
	}
	
	// CITIES INITIALIZATION:
	std::vector<json> cityListJSON = j["cities"];

	for (int i = 0; i < cityListJSON.size(); i++) {
		auto cityJSON = cityListJSON.at(i);

		auto cityName = cityJSON["name"].get<std::string>();

	}


}

//int main() {
//	readGameFromFile("save.json");
//	system("pause");
//
//}
