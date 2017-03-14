#include "Map.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

Map::Map(const std::string& name, City* const startingCity, std::vector<std::unique_ptr<City>> cities)
	: _name { name }
	, _cities { std::move(cities) }
	, _startingCity { startingCity }
{}

std::string Map::name() const
{
	return _name;
}

std::string& Map::name()
{
	return _name;
}

City& Map::addCity(CityPtr city)
{
	_cities.push_back(std::move(city));
	return *_cities.back().get();
}

void Map::removeCity(const City& city)
{
	std::remove_if(_cities.begin(), _cities.end(), [&](const auto& c)
	{
		return *c == city;
	});
}

std::vector<City*> Map::stations() const
{
	std::vector<City*> list;
	for (const auto& city : _cities)
	{
		if (city->hasResearchStation())
		{
			list.push_back(city.get());
		}
	}
	return list;
}

std::map<std::string, City*> Map::nameMap() const
{
	std::map<std::string, City*> map;
	for (const auto& city : _cities)
	{
		map[city->name()] = city.get();
	}
	return map;
}

City& Map::findCityByName(const std::string& name) const
{
	const auto it = std::find_if(_cities.begin(), _cities.end(), [&](const std::unique_ptr<City>& city) { return city->name() == name; });
	if (it == _cities.end())
	{
		throw std::out_of_range { "No city of that name exits." };
	}
	return *it->get();
}

City* Map::findCityIfContained(const std::string& name) const
{
	City* p = nullptr;
	if (contains(name))
	{
		p = &findCityByName(name);
	}
	return p;
}

bool Map::contains(const std::string& name) const
{
	return std::any_of(_cities.begin(), _cities.end(), [&](const auto& city) { return city->name() == name; });
}

City& Map::startingCity() const
{
	return *_startingCity;
}

City *& Map::startingCity()
{
	return _startingCity;
}

const std::vector<Map::CityPtr>& Map::cities() const
{
	return _cities;
}
