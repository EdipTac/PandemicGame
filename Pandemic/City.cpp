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
	, _infected {false}
	, _quarantined {false}
{} // Empty

std::string City::name() const
{
	return _name;
}

std::string& City::name()
{
	return _name;
}

Colour City::colour() const
{
	return _colour;
}

Colour& City::colour()
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

size_t City::diseaseCubes(const Colour& colour) const
{
	return _diseaseCubes[colour];
}

size_t& City::diseaseCubes(const Colour& colour)
{
	return _diseaseCubes[colour];
}
int City::totalCubes() {
	int sum = 0;
	for (auto& color : diseases()) {
		sum += diseaseCubes(color);
	}
	return sum;
}

void City::setDiseaseCubes(const Colour& colour, int quantity) 
{
	_diseaseCubes[colour] = quantity;
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

void City::disconnectFrom(City& target)
{
	{
		auto it = std::find_if(_connections.begin(), _connections.end(), [&](const auto& c)
		{
			return *c == target;
		});
		if (it != _connections.end())
		{
			_connections.erase(it);
		}
	}
	{
		auto it = std::find_if(target._connections.begin(), target._connections.end(), [&](const auto& c)
		{
			return *c == *this;
		});
		if (it != target._connections.end())
		{
			target._connections.erase(it);
		}
	}

}

void City::addDiseaseCubes(const Colour& colour, const unsigned amount, Board& state){
	if (!_outbreaks[colour] && !_quarantined && !state.cubePool().isEradicated(colour)) {
		_diseaseCubes.takeFrom(colour, amount, state.cubePool());
		if (_diseaseCubes[colour] > cubesBeforeOutbreak) {

		    _outbreaks[colour] = true;
            state.advanceOutbreakCounter();
            _diseaseCubes.giveTo(colour, (_diseaseCubes.operator[](colour) - cubesBeforeOutbreak), state.cubePool());
            for (const auto& city : connections()){
				city->addDiseaseCubes(colour, cubesPerInfection, state);
			}
		}
	}
}


void City::removeDiseaseCubes(const Colour& colour, const unsigned amount, CubePool& pool){

	_diseaseCubes.giveTo(colour, amount, pool);
}

bool City::isInfected() const
{
	return _infected;
}

void City::infect()
{
	_infected = true;
}


bool City::isQuarantined() const
{
	return _quarantined;
}

void City::quarantine()
{
	_quarantined = true;
}

bool City::hasResearchStation() const
{
	return _hasResearchStation;
}

bool& City::hasResearchStation()
{
	return _hasResearchStation;
}

void City::giveResearchStation(Board& game)
{
	game.removeResearchStation();
	_hasResearchStation = true;
}

void City::removeResearchStation(Board& game)
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
	ss << "Is quarantined: " << isQuarantined();
	ss << "\nHas research station: " << hasResearchStation();
	ss << "\nOutbreak status:\n";
	for (const auto& colour : colours())
	{
		ss << "\t" << colourName(colour) << ": " << diseaseOutbreak(colour) << "\n";
	}
	if (_connections.empty())
	{
		ss << "No connections.\n";
	}
	else
	{
		ss << "Connected to:\n";
		for (const auto& connection : _connections)
		{
			ss << "\t" << connection->_name << "\n";
		}
	}
	ss << std::endl;
	return ss.str();
}

bool operator==(const City& lhs, const City& rhs)
{
	return lhs._name == rhs._name;
}
