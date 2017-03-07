#include "Map.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

Map::Map(const std::string& name, City* const startingCity, std::vector<std::unique_ptr<City>> cities)
	: _name { name }
	, _cities { std::move(cities) }
	, _startingCity { *startingCity }
{}

std::string Map::name() const
{
	return _name;
}

City& Map::addCity(CityPtr city)
{
	_cities.push_back(std::move(city));
	return *_cities.back().get();
}

Player& Map::addPlayer(const std::string& name)
{
	_players.push_back(std::make_unique<Player>());
	auto& player = *_players.back();
	player.setName(name);
	return player;
}

City& Map::city(const std::string& name) const
{
	const auto it = std::find_if(_cities.begin(), _cities.end(), [&](const std::unique_ptr<City>& cityPtr) -> bool
	{
		return cityPtr->name() == name;
	});
	if (it == _cities.end())
	{
		throw std::out_of_range { "No city of that name exits." };
	}
	return *it->get();
}

bool Map::contains(const std::string& name) const
{
	return std::any_of(_cities.begin(), _cities.end(), [&](const std::unique_ptr<City>& cityPtr) -> bool
	{
		return cityPtr->name() == name;
	});
}

City& Map::startingCity() const
{
	return _startingCity;
}

const std::vector<Map::CityPtr>& Map::cities() const
{
	return _cities;
}

const std::vector<Map::PlayerPtr>& Map::players() const
{
	return _players;
}