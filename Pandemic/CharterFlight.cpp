#include "CharterFlight.h"
#include "Player.h"
#include "Board.h"
#include "City.h"

action::CharterFlight::CharterFlight(Player * const performer)
	: Action{"Charter Flight", "Discard a city card matching the city you are in to fly to any other city.", performer} {}

void action::CharterFlight::solicitData()
{
	// Reset
	_target = nullptr;

	// Aliases
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

	// Get city choice from player, move, and discard card
	std::cout << "Where would you like to fly to? ";
	std::string input;
	while (true)
	{
		const auto& cities = Board::instance().map().cityView();
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(cities.begin(), cities.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != cities.end())
		{
			_target = *it;
			break;
		}
		std::cout << "No city of that name.\n";
	}
}

void action::CharterFlight::perform()
{
	_performer->discard(*_performer->positionCard(), Board::instance().playerDeck());
	_performer->moveTo(*_target);
}

bool action::CharterFlight::isValid() const
{
	return _performer && _target;
}
