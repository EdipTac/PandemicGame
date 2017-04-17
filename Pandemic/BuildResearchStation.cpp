#include "BuildResearchStation.h"
#include "Player.h"
#include "Board.h"
#include "City.h"
#include "PlayerCard.h"
#include "Menu.h"
#include "MenuUtils.h"

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
		return;
	}

	_positionCard = player.positionCard();
	// Without the position card, you cannot perform this action
	if (!_positionCard)
	{
		std::cout << "You don't have any city cards that match your position.\n";
		return;
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

		// List cards, get player target, discard card, and move
		auto menu = cityMenu(stations);
		menu.setMessage("Select a City to take a Research Station from: ");
		_target = menu.solicitInput();
		_takeFromCity = _target;
	}
}

void action::BuildResearchStation::perform()
{
	if (_takeFromCity)
	{
		_target->removeResearchStation();
	}
	
	// Remove card, place station
	_performer->discard(*_positionCard, Board::instance().playerDeck());
	_performer->pawn().position().giveResearchStation();
}

bool action::BuildResearchStation::isValid() const
{
	return _performer && _positionCard;
}
