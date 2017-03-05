#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Colour.h"

// Represents a single city.
// Each city should belong to a map. A city has a name and a coloured "region" that it belongs to, for the purposes of disease classification.
// A city can be connected to other cities that belong to its same map.
class City
{
public:
	// Constructor
	City(const std::string& name = "", const Colour& colour = Colour::Black);

	// Accessors
	std::string name() const;								// The city's name
	Colour colour() const;									// The coloured "region" the city belongs to
	const std::vector<City*>& connections() const;			// The cities that this city is connected to
	bool isConnectedTo(const City& target);					// True iff the city is connected to another given city
	unsigned int diseaseCubes(const Colour& colour) const;

	// Mutators
	City& name(const std::string& name);								// Changes the city's name
	City& colour(const Colour& colour);									// Changes the city's coloured region
	City& connectTo(City& target);										// Declares that this city is connected to another given city
	City& addDiseaseCubes(const Colour& colour, const unsigned int amount);
	City& removeDiseaseCubes(const Colour& colour, const unsigned int amount);

private:
	std::string _name;
	Colour _colour;
	std::vector<City*> _connections;
	std::map<Colour, unsigned int> _diseaseCubes;
	bool outbreak; 
};
