#include <algorithm>

#include "Dispatch.h"
#include "Board.h"
#include "Player.h"

const std::string desc = "Move any pawn to any city containing another pawn.";

action::Dispatch::Dispatch(Player* const performer)
	: Action { "Dispatch", desc, performer }
{}

void action::Dispatch::solicitData()
{
	// Get other players, if any
	auto others = Board::instance().players();
	std::remove_if(others.begin(), others.end(), [&](const auto& p)
	{
		return p == this->_performer;
	});

	if (others.empty())
	{
		std::cout << "No other players.\n";
		return;
	}

	// List other players
	std::cout << "Who to move?\n";
	for (const auto& player : others)
	{
		std::cout << "\t" << player->name() << "\n";
	}

	// Get dispatchee from player
	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(others.begin(), others.end(), [&](const auto& p)
		{
			return input == p->name();
		});
		if (it != others.end())
		{
			_dispatchee = *it;
			break;
		}
		std::cout << "No player of that name.\n";
	}

	// Remove dispatchee from list of possible destinations
	std::remove(others.begin(), others.end(), _dispatchee);

	// Get possbile destinations: ther pawn locations...
	std::vector<City*> destinations;	
	for (const auto& player : others)
	{
		auto city = &player->pawn().position();
		if (std::find(destinations.begin(), destinations.end(), city) == destinations.end())
		{
			// Not already in list
			destinations.push_back(city);
		}
	}

	// ...or connected cities ("regular" move)
	for (const auto& city : _dispatchee->pawn().position().connections())
	{
		destinations.push_back(city);
	}

	// List possible destinations
	std::cout << "Where to move to?\n";
	for (const auto& city : destinations)
	{
		std::cout << "\t" << city->name() << "\n";
	}

	// Get destination from player
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(destinations.begin(), destinations.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != destinations.end())
		{
			_destination = *it;
			break;
		}
		std::cout << "No city of that name.\n";
	}
}

void action::Dispatch::perform()
{
	_dispatchee->pawn().setPosition(*_destination);
}

bool action::Dispatch::isValid() const
{
	return _dispatchee && _destination;
}
