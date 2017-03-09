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

	//std::unique_ptr<GameState> gameState;

	//// read and store the map information
	//gameState->setMap(readMapFromFile(j["map"].get<std::string>()));
	
	std::vector<json> playerListJSON = j["players"];
	std::vector<std::unique_ptr<Player>> players;

	//for (auto i = playerListJSON.begin(); i != playerListJSON.end(); ++i) {
	//	//players.push_back(std::make_unique<Player>(*i));
	//	std::cout << *i << "\n";
	//}

	for (int i=0; i < playerListJSON.size(); i++) {
		//std::cout << playerListJSON.at(i)["name"].get<std::string>() << "\n";
		auto playerJSON = playerListJSON.at(i);
		std::unique_ptr<Player> player;

		// parse and set the player's name
		player->setName(playerJSON["name"].get<std::string>());

		// parse and set the player's position
		


		// parse and set the player's role
		auto roleName = playerJSON["role"].get<std::string>();

		// search the hardcoded roles to find appropriate RoleCard
		//RoleCard::getRoleWithName(roleName);


		// parse and set the player's hand (of PlayerCards)



		// store this player into the vector of players
		//players.push_back(std::move(player));
	}

	


}

int main() {
	readGameFromFile("save.json");
	system("pause");

}
