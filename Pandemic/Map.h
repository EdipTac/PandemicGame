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
	using CityPtr = std::unique_ptr<City>;
	using PlayerPtr = std::unique_ptr<Player>;

public:
	// Constructs a map with a given file name
	Map(const std::string& name, City* const startingCity, std::vector<std::unique_ptr<City>> cities = {});

	// Accessors
	std::string name() const;						// Map file name
	City& city(const std::string& name) const;		// Find a city by name
	bool contains(const std::string& name) const;	// True iff map contains city of given name
	City& startingCity() const;
	const std::vector<CityPtr>& cities() const;		// List of pointers to all contained cities
	const std::vector<PlayerPtr>& players() const;	// List of pointers to contained players

	// Mutators
	City& addCity(CityPtr city);					// Add city
	Player& addPlayer(const std::string& name);		// Add a player with a given name

private:
	std::string _name;
	std::vector<CityPtr> _cities;
	City& _startingCity;
	std::vector<PlayerPtr> _players;
};
