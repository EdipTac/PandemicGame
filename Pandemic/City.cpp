#include <algorithm>
#include <stdexcept>
#include <sstream>

#include "City.h"
#include "Colour.h"
#include "InfectionCardDeck.h"

City::City(const std::string& name, const Colour& colour, const std::map<Colour, size_t>& cubes)
	: _name { name }
	, _colour { colour }
	, _diseaseCubes { cubes }
    , _outbreaks
	 {
		{ Colour::Black,	false	},
		{ Colour::Blue,		false	},
		{ Colour::Red,		false	},
		{ Colour::Yellow,	false	}
	 }
	, _quarantined {false}
{} // Empty

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

bool City::isConnectedTo(const City& target) const
{
	return std::any_of(_connections.begin(), _connections.end(), [&](const auto& city) { return city == &target; });
}

size_t& City::diseaseCubes(const Colour& colour)
{
	return _diseaseCubes[colour];
}

bool City::diseaseOutbreak(const Colour& colour) const
{
	return _outbreaks.at(colour);
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

void City::addDiseaseCubes(const Colour& colour, const unsigned amount, CubePool& source, InfectionCardDeck& infectionDeck)
{
	if (!_outbreaks[colour] && !_quarantined && ! source.isEradicated(colour)) {
		_diseaseCubes.takeFrom(colour, amount, source);
		if (_diseaseCubes[colour] > MAX_CUBE_PER_DISEASE) {
			_outbreaks[colour] = true;
			infectionDeck.moveOutbreakMarker();
			_diseaseCubes.giveTo(colour, (_diseaseCubes.operator[](colour) - MAX_CUBE_PER_DISEASE), source);// may change source to a garbage CubePool
			for (const auto& city : connections())
			{
				city->addDiseaseCubes(colour, CUBE_PER_INFECTION, source, infectionDeck);
			}
		}

	}

}

void City::removeDiseaseCubes(const Colour& colour, const unsigned amount, CubePool& source)
{
	_diseaseCubes.giveTo(colour, amount, source);
}

bool City::hasResearchStation() const
{
	return _hasResearchStation;
}

void City::giveResearchStation(GameState& game)
{
	game.removeResearchStation();
	_hasResearchStation = true;
}

void City::removeResearchStation(GameState& game)
{
	game.returnResearchStation();
	_hasResearchStation = false;
}

std::vector<Colour> City::diseases()
{
	std::vector<Colour> d;
	for (const auto& colour : colours())
	{
		if (_diseaseCubes[colour] > 0)
		{
			d.push_back(colour);
		}
	}
	return d;
}

std::string City::string()
{
	std::stringstream ss;
	ss << name();
	ss << " Colour: " << colourName(colour());
	ss << "\nInfection status:\n";
	for (const auto& colour : colours())
	{
		ss << "\t" << colourName(colour) << ": " << diseaseCubes(colour) << "\n";
	}
	ss << "Is quarantined: " << quarantined();
	ss << "\nHas research station: " << hasResearchStation();
	ss << "\nOutbreak status:\n";
	for (const auto& colour : colours())
	{
		ss << "\t" << diseaseOutbreak(colour) << "\n";
	}
	ss << std::endl;
	return ss.str();
}

bool operator==(const City& lhs, const City& rhs)
{
	return lhs._name == rhs._name;
}
