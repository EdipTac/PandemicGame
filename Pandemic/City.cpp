#include <algorithm>
#include <stdexcept>

#include "City.h"
#include "Colour.h"

City::City(const std::string& name, const Colour& colour)
	: _name { name }
	, _colour { colour }
	, _diseaseCubes { 0 }
	/*, _outbreaks {false}*/
	, _quarantined {false}
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
	if (!_outbreaks[colour] && !_quarantined && ! source.isEradicated(colour)) {
		_diseaseCubes.takeFrom(colour, amount, source);
		if (_diseaseCubes[colour] > MAX_CUBE_PER_DISEASE) {
			_outbreaks[colour] = true;
			_diseaseCubes.giveTo(colour, (_diseaseCubes.operator[](colour) - MAX_CUBE_PER_DISEASE), source);// may change source to a garbage CubePool
			for (const auto& city : connections())
			{
				city->addDiseaseCubes(colour, CUBE_PER_INFECTION, source);
			}
		}

	}

}

void City::removeDiseaseCubes(const Colour& colour, const unsigned int amount, CubePool& source)
{
	_diseaseCubes.giveTo(colour, amount, source);
}
