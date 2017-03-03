#include <algorithm>
#include <stdexcept>

#include "City.h"
#include "Colour.h"

City::City(const std::string& name, const Colour& colour)
	: _name { name }
	, _colour { colour }
	, _diseaseCubes { 0 }
{
	// Empty
}

std::string City::name() const
{
	return _name;
}

Colour City::colour() const
{
	return _colour;
}

const std::vector<City*>& City::connections() const
{
	return _connections;
}

bool City::isConnectedTo(const City& target)
{
	return std::any_of(_connections.begin(), _connections.end(), [&](const City* city) -> bool { return city == &target; });
}

unsigned int City::diseaseCubes(const Colour& colour) const
{
	return _diseaseCubes[colour];
}

void City::name(const std::string& name)
{
	_name = name;
}

void City::colour(const Colour& colour)
{
	_colour = colour;
}

void City::connectTo(City &target)
{
	if (!isConnectedTo(target))
	{
		_connections.push_back(&target);
	}
}

void City::addDiseaseCubes(const Colour& colour, const unsigned int amount, CubePool& source)
{
	_diseaseCubes.takeFrom(colour, amount, source);
}

void City::removeDiseaseCubes(const Colour& colour, const unsigned int amount, CubePool& source)
{
	_diseaseCubes.giveTo(colour, amount, source);
}
