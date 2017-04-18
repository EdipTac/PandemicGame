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

void Map::setName(const std::string & name)
{
	_name = name;
}

City& Map::addCity(std::unique_ptr<City> city)
{
	if (contains(city->name()))
	{
		throw std::invalid_argument("A city of this name already exists.");
	}
	_cacheValid = false;
	_cities.push_back(std::move(city));
	return *_cities.back().get();
}

void Map::removeCity(const City& city)
{
	_cacheValid = false;
	_cities.erase(std::find_if(_cities.begin(), _cities.end(), [&](const auto& c)
	{
		return *c == city;
	}));
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

std::vector<City*> Map::cities() const
{
	if (!_cacheValid)
	{
		_cityViewCache.clear();
		for (const auto& city : _cities)
		{
			_cityViewCache.push_back(city.get());
		}
		_cacheValid = true;
	}
	return _cityViewCache;
}
