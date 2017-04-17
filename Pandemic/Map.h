#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "City.h"
#include "Player.h"

// Represents a game map. Contains players and cities
class Map
{
public:
	// Constructs a map with a given file name
	Map(const std::string& name = "", City* const startingCity = nullptr, std::vector<std::unique_ptr<City>> cities = {});

	// Map file name
	std::string name() const;
	std::string& name();
	void setName(const std::string& name);

	// Find a city by name
	City& findCityByName(const std::string& name) const;

	// Find a city by name. Returns nullptr if not found.
	City* findCityIfContained(const std::string& name) const;

	// True iff map contains city of given name
	bool contains(const std::string& name) const;

	// The map's starting city
	City& startingCity() const;
	City*& startingCity();

	// List of pointers to all contained cities
	std::vector<City*> cities() const;

	// Add a city
	City& addCity(std::unique_ptr<City> city);

	// Remove a city
	void removeCity(const City& city);

	// List of all cities with a research station
	std::vector<City*> stations() const;

private:
	std::string _name;
	std::vector<std::unique_ptr<City>> _cities;
	mutable std::vector<City*> _cityViewCache;
	mutable bool _cacheValid = false;
	City* _startingCity;
};
