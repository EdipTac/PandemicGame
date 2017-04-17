#include "CharterFlight.h"
#include "Player.h"
#include "Board.h"
#include "City.h"
#include "MenuUtils.h"

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
	auto menu = namedMenu(Board::instance().map().cities());
	menu.setMessage("Where would you like to fly to? ");
	_target = menu.solicitInput();
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
