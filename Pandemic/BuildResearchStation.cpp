#pragma warning (disable: 4800)

#include "BuildResearchStation.h"
#include "Player.h"
#include "Board.h"


action::BuildResearchStation::BuildResearchStation(Player * const performer)
	: Action{"Build Research Station", "Player discards a card matching the city they are in to build a research station", performer} {}

void action::BuildResearchStation::solicitData()
{
	auto& player = *_performer;
	const auto& cards = player.cityCards();

	// You can't discard a card if you have none!
	if (cards.empty())
	{
		std::cout << "You have no city cards.\n";
	}

	// Without the position card, you cannot perform this action
	if (!player.hasPositionCard())
	{
		std::cout << "You don't have any city cards that match your position.\n";
	}

	// If there are no remaining research stations, we have to steal from another city
	if (!Board::instance().hasResearchStation())
	{
		auto stations = Board::instance().map().stations(); // Alias
		{
			// Remove your current city from the list of potential targets
			stations.erase(std::find_if(stations.begin(), stations.end(), [&](const auto& c)
			{
				return *c == player.pawn().position();
			}));
		}

		// No targets
		if (stations.empty())
		{
			std::cout << "No research stations left to build.\n";
		}

		_takeFromCity = true;
		// set the _target
		// List cards, get player target, discard card, and move
		std::cout << "Select a City to take a Research Station from: \n";
		for (const auto& city : stations)
		{
			std::cout << "\t" << city->name() << "\n";
		}

		std::string input;
		while (true)
		{
			std::getline(std::cin >> std::ws, input);
			const auto& it = std::find_if(stations.begin(), stations.end(), [&](const auto& c)
			{
				return input == c->name();
			});
			if (it != stations.end())
			{
				_target = *it;
				break;
			}
			std::cout << "No city of that name.\n";
		}
	}
}

void action::BuildResearchStation::perform()
{
	if (_takeFromCity) {
		_target->removeResearchStation(Board::instance());
	}
	
	// Remove card, place station
	const auto& cards = _performer->cards();
	const auto& positionName = _performer->pawn().position().name();
	auto it = std::find_if(cards.begin(), cards.end(), [&](const auto& card)
	{
		return card->name() == positionName;
	});
	_performer->discard(**it, Board::instance().playerDeck());
	_performer->pawn().position().giveResearchStation(Board::instance());
}

bool action::BuildResearchStation::isValid() const
{
	return _performer;
}
