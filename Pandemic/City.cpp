#include <algorithm>
#include <stdexcept>
#include <sstream>

#include "City.h"
#include "Colour.h"
#include "Board.h"
#include "Player.h"
#include "Board.h"
#include "Util.h"

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

size_t City::totalCubes() {
	size_t sum = 0;
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

void City::addDiseaseCubes(const Colour& colour, const size_t amount)
{
	if (!_outbreaks[colour] && !_quarantined && !Board::instance().cubePool().isEradicated(colour)) {
		_diseaseCubes.takeFrom(colour, amount, Board::instance().cubePool());
		if (_diseaseCubes[colour] > cubesBeforeOutbreak) {

		    _outbreaks[colour] = true;
			Board::instance().advanceOutbreakCounter();
            _diseaseCubes.giveTo(colour, (_diseaseCubes.operator[](colour) - cubesBeforeOutbreak), Board::instance().cubePool());
            for (const auto& city : connections()){
				city->addDiseaseCubes(colour, cubesPerInfection);
			}
		}
	}
}


void City::removeDiseaseCubes(const Colour& colour, const size_t amount, CubePool& pool){

	_diseaseCubes.giveTo(colour, amount, pool);
}

void City::removeAllDiseaseCubes(const Colour& colour, CubePool& pool)
{
	removeDiseaseCubes(colour, _diseaseCubes[colour], pool);
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

void City::isQuarantined(const bool is)
{
	_quarantined = is;
}

bool City::hasResearchStation() const
{
	return _hasResearchStation;
}

bool& City::hasResearchStation()
{
	return _hasResearchStation;
}

void City::giveResearchStation()
{
	Board::instance().removeResearchStation();
	_hasResearchStation = true;
}

void City::removeResearchStation()
{
	Board::instance().returnResearchStation();
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
	ss << " (" << colourName(colour()) << ")";
	
	ss << "\nInfection status:\n";
	for (const auto& colour : colours())
	{
		ss << "  " << colourName(colour);
	}
	ss << "\n  ";
	for (const auto& colour : colours())
	{
		ss << diseaseCubes(colour) << spaces(colourName(colour).size() + 1);
	}
	ss << "\n";

	if (isQuarantined())
	{
		ss << "Quarantined\n";
	}
	if (hasResearchStation())
	{
		ss << "Research station present\n";
	}

	if (_connections.empty())
	{
		ss << "No connections.\n";
	}
	else
	{
		ss << "Connected to ";
		for (auto it = _connections.begin(); it != _connections.end(); ++it)
		{
			ss << (*it)->_name;
			if (it + 1 != _connections.end())
			{
				ss << ", ";
			}
			else
			{
				ss << ".\n";
			}
		}
	}
	ss << std::endl;
	return ss.str();
}

void City::onEnter(Player& player)
{
	player.role().onEnter(*this);
}

void City::onExit(Player& player)
{
	player.role().onExit(*this);
}

bool operator==(const City& lhs, const City& rhs)
{
	return lhs._name == rhs._name;
}
