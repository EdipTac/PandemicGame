#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Colour.h"
#include "CubePool.h"

class GameState;
class InfectionCardDeck;

// Represents a single city.
// Each city should belong to a map. A city has a name and a coloured "region" that it belongs to, for the purposes of disease classification.
// A city can be connected to other cities that belong to its same map.
class City
{
public:
	static const unsigned cubesPerInfection = 1;
	static const unsigned cubesBeforeOutbreak = 3;

	// Constructs a city with a given name, colour, and disease cube count
	City(const std::string& name = "", const Colour& colour = Colour::Black, const std::map<Colour, size_t>& cubes = {});

	City(const City&) = delete;
	City(City&&) = default;
	City& operator=(const City&) = delete;
	City& operator=(City&&) = default;

	// The city's name
	std::string name() const;
	std::string& name();
	void name(const std::string& name);

	// The coloured "region" the city belongs to
	Colour colour() const;
	Colour& colour();
	void colour(const Colour& colour);

	// The cities that this city is connected to
	const std::vector<City*>& connections() const;

	// True iff the city is connected to another given city
	bool isConnectedTo(const City& target) const;

	// Declares that this city is connected to another given city
	void connectTo(City& target);
	void disconnectFrom(City& target);

	// The number of disease cubes of a given colour the city has
	size_t diseaseCubes(const Colour& colour) const;
	size_t& diseaseCubes(const Colour& colour);

	// set the number of disease cubes in a City - used for the game loading
	void setDiseaseCubes(const Colour& colour, int quantity);

	// The outbreak status of each disease
	bool diseaseOutbreak(const Colour& colour) const;

	// Adds disease cubes of a given colour from a given source
	void addDiseaseCubes(const Colour& colour, const unsigned amount, CubePool& source, InfectionCardDeck& infectionDeck);

	// Removes disease cubes of a given colour from a given source
	void removeDiseaseCubes(const Colour& colour, const unsigned amount, CubePool& source);
	
	// True iff quarantine specialist locates at this city or at cities with direct connection with this city
	bool isQuarantined() const;

	// Sets quarantine to true
	void quarantine();
	
	// True iff the city has a research station
	bool hasResearchStation() const;
	bool& hasResearchStation();
	void giveResearchStation(GameState& game);
	void removeResearchStation(GameState& game);

	// List of all diseases in this city
	std::vector<Colour> diseases();

	// True iff the two cities share a name
	friend bool operator==(const City& lhs, const City& rhs);

	// Returns a report on the city
	std::string string();

	class Builder;

private:

	std::string _name;
	Colour _colour;
	std::vector<City*> _connections;
	CubePool _diseaseCubes;
    std::map<Colour, bool> _outbreaks;
	bool _quarantined;
	bool _hasResearchStation = false;
};

class City::Builder
{
public:
	Builder& name(const std::string& name)
	{
		_name = name;
		return *this;
	}

	Builder& colour(const Colour& colour)
	{
		_colour = colour;
		return *this;
	}

	Builder& cubes(const Colour& colour, const size_t count)
	{
		_cubes[colour] = count;
		return *this;
	}

	City build() const
	{
		return { _name, _colour, _cubes };
	}

	std::unique_ptr<City> buildUnique() const
	{
		return std::make_unique<City>(_name, _colour, _cubes);
	}

private:
	std::string _name;
	Colour _colour;
	std::map<Colour, size_t> _cubes;
};
