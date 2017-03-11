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
	// Constructs a city with a given name and colour.
	City(const std::string& name = "", const Colour& colour = Colour::Black);

	//    ----  Accessors  ----

	// The city's name
	std::string name() const;

	// The coloured "region" the city belongs to
	Colour colour() const;

	// The cities that this city is connected to
	const std::vector<City*>& connections() const;

	// True iff the city is connected to another given city
	bool isConnectedTo(const City& target) const;

	// The number of disease cubes of a given colour the city has
	unsigned diseaseCubes(const Colour& colour) const;
	// The outbreak status of each disease
	bool diseaseOutbreak(const Colour& colour) const;

	//    ----  Mutators  ----

	// Changes the city's name
	void name(const std::string& name);

	// Changes the city's coloured region
	void colour(const Colour& colour);

	// Declares that this city is connected to another given city
	void connectTo(City& target);

	// Adds disease cubes of a given colour from a given source
	void addDiseaseCubes(const Colour& colour, const unsigned amount, CubePool& source, InfectionCardDeck& infectionDeck);

	// Removes disease cubes of a given colour from a given source
	void removeDiseaseCubes(const Colour& colour, const unsigned amount, CubePool& source);
	
	// True iff quarantine specialist locates at this city or at cities with direct connection with this city
	bool quarantined() const {
		return _quarantined;
	}
	void setQuarantined() {
		_quarantined = true;
	}
	

	bool hasResearchStation() const;
	void giveResearchStation(GameState& game);
	void removeResearchStation(GameState& game);

	std::vector<Colour> diseases() const;

	friend bool operator==(const City& lhs, const City& rhs);

private:
	std::string _name;
	Colour _colour;
	std::vector<City*> _connections;
	CubePool _diseaseCubes;
	//Hold outbreak boolean of each colour
    std::map < Colour, bool> _outbreaks;
	//Whether the city is quarantined
	bool _quarantined;
	// Maximum cuber per colour each city can hold
	unsigned const MAX_CUBE_PER_DISEASE = 3;
	// Place one cube for each infection
	unsigned const CUBE_PER_INFECTION = 1;
	bool _hasResearchStation = false;
};
