#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Colour.h"
#include "CubePool.h"

class Board;
class Player;

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
	void addDiseaseCubes(const Colour& colour, const size_t amount);

	// Removes disease cubes of a given colour, giving back to a given source
	void removeDiseaseCubes(const Colour& colour, const size_t amount, CubePool& pool);

	// Removes all disease cubes of a given colour, giving back to a given source
	void removeAllDiseaseCubes(const Colour& colour, CubePool& pool);

	// True iff city is infected, only for the purpose of statistic
	bool isInfected() const;

	// Sets infect status to true, only for the purpose of statistic
	void infect();
	
	// True iff quarantine specialist locates at this city or at cities with direct connection with this city
	bool isQuarantined() const;

	// Sets quarantine to true
	void isQuarantined(const bool is);
	
	// True iff the city has a research station
	bool hasResearchStation() const;
	bool& hasResearchStation();
	void giveResearchStation();
	void removeResearchStation();

	// List of all diseases in this city
	std::vector<Colour> diseases();

	// True iff the two cities share a name
	friend bool operator==(const City& lhs, const City& rhs);

	// Returns a report on the city
	std::string string();
	
	// Sum up total cube numbers in the city
	size_t totalCubes();

	// Called when a player enters the city - calls the player role's onEnter(City&)
	void onEnter(Player& player);
	void onExit(Player& player);

private:

	std::string _name;
	Colour _colour;
	std::vector<City*> _connections;
	CubePool _diseaseCubes;
    std::map<Colour, bool> _outbreaks;
	bool _quarantined;
	bool _infected;
	bool _hasResearchStation = false;
};
