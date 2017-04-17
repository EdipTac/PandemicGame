#include <algorithm>

#include "Dispatch.h"
#include "Board.h"
#include "Player.h"
#include "MenuUtils.h"

const std::string desc = "Move any pawn to any city containing another pawn.";

action::Dispatch::Dispatch(Player* const performer)
	: Action { "Dispatch", desc, performer }
{}

void action::Dispatch::solicitData()
{
	// Reset
	_dispatchee = nullptr;
	_destination = nullptr;

	// Get other players, if any
	std::vector<Player*> others;
	for (const auto& player : Board::instance().players())
	{
		if (player != _performer)
		{
			others.push_back(player);
		}
	}

	if (others.empty())
	{
		std::cout << "No other players.\n";
		return;
	}

	// Get dispatchee from player
	_dispatchee =
		namedMenu(others)
		.setMessage("Who to move? ")
		.solicitInput();

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
		if (std::find(destinations.begin(), destinations.end(), city) == destinations.end())
		{
			// Not already in list
			destinations.push_back(city);
		}
	}

	// List possible destinations and get destination from player
	_destination =
		namedMenu(destinations)
		.setMessage("Where to move to? ")
		.solicitInput();
}

void action::Dispatch::perform()
{
	_dispatchee->moveTo(*_destination);
}

bool action::Dispatch::isValid() const
{
	return _dispatchee && _destination;
}
