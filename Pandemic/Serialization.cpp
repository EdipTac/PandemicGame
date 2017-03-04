#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <tuple>

#include "Colour.h"
#include "Serialization.h"

bool fileExists(const std::string& fileName)
{
	return std::fstream { fileName }.good();
}

Map readMapFromFile(const std::string& fileName)
{
	throw std::logic_error { "Not implemented." };
	std::vector<std::string> playerNames;
	std::map<std::string, std::string> playerLocations;
	std::vector<std::string> cityNames;
	std::map<std::string, std::string> colours;
	std::map<std::string, std::vector<std::string>> connections;
	std::ifstream stream{ fileName };
	if (!stream)
	{
		throw std::runtime_error{ "File not found!" };
	}
	while (!stream.eof())
	{
		std::string line;
		std::getline(stream, line);
		if (line[0] == '/' || line.empty())
		{
			// Skip comments started with "/" or blank lines
			continue;
		}
		else if (line.back() == ':')
		{
			playerNames.push_back(line.substr(0, line.size() - 1));
		}
		else if (line.front() == '@')
		{
			playerLocations[playerNames.back()] = line.substr(1);
		}
		else if (line[0] == '\t')
		{
			connections[cityNames.back()].push_back(line.substr(1));
		}
		else
		{
			const auto idx = line.find_last_of(' ');
			const auto cityName = line.substr(0, idx);
			const auto colour = line.substr(idx + 1);
			cityNames.push_back(cityName);
			connections[cityName];
			colours[cityName] = colour;
		}
	}
	stream.close();

	Map map(fileName);

	// Add cities
	for (const auto& pair : connections)
	{
		map.addCity(std::make_unique<City>(pair.first));
	}

	// Add connections
	for (const auto& pair : connections)
	{
		auto& source = map.city(pair.first);
		for (const auto& targetName : pair.second)
		{
			auto& target = map.city(targetName);
			source.connectTo(target);
		}
	}

	// Add players and pawn locations
	for (const auto& name : playerNames)
	{
		map.addPlayer(name);
		//map.players().back()->pawn().position(map.city(playerLocations[name]));
	}

	return map;
}

void writeMapToFile(const Map& map, const std::string& fileName)
{
	throw std::logic_error { "Not implemented." };
	std::map<std::string, std::string> players;
	for (const auto& player : map.players())
	{
		//players[player->name()] = player->pawn().position().name();
	}

	std::map<std::string, std::pair<std::string, std::vector<std::string>>> cities;
	for (const auto& source : map.cities())
	{
		const auto& connections = source->connections();
		cities[source->name()].first = colourToString(source->colour());
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
