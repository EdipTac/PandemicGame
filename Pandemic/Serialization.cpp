#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <tuple>

#include "Colour.h"
#include "Serialization.h"
#include "Util.h"

bool fileExists(const std::string& fileName)
{
	return std::fstream { fileName }.good();
}

std::string getline(std::ifstream& fs)
{
	std::string line;
	std::getline(fs, line);
	return line;
}

std::unique_ptr<Map> readMapFromFile(const std::string& fileName)
{
	std::ifstream fs { fileName };
	if (!fs)
	{
		throw std::runtime_error { "File not found!" };
	}

	std::vector<std::unique_ptr<City>> cities;
	std::map<City*, std::vector<std::string>> connections;
	while (!fs.eof())
	{
		const auto line = getline(fs);
		if (line == "</cities>")
		{
			break;
		}
		else if (line.empty())
		{
			continue;
		}
		else if (line[0] != '\t')
		{
			std::string name, colour;
			std::tie(name, colour) = splitOnLastSpace(line);
			cities.push_back(std::make_unique<City>(name, colourFromAbbreviation(colour)));
			connections[cities.back().get()];
		}
		else
		{
			connections[cities.back().get()].push_back(line.substr(1));
		}
	}

	auto map  = std::make_unique<Map>(fileName, std::move(cities));

	for (const auto& list : connections)
	{
		for (const auto& targetName : list.second)
		{
			auto& target = map->city(targetName);
			list.first->connectTo(target);
		}
	}

	return std::move(map);
}

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
