#include "MoveFromResearchStation.h"
#include "Player.h"
#include "City.h"
#include "PlayerCityCard.h"
#include "Board.h"
#include "MenuUtils.h"

const std::string desc = "Move from a research station to any city by discarding any City card.";

action::MoveFromResearchStation::MoveFromResearchStation(Player* const performer)
	: Action { "Move from a research station", desc, performer }
{}

action::MoveFromResearchStation::~MoveFromResearchStation() {}

void action::MoveFromResearchStation::solicitData()
{
	// Reset
	_destination = nullptr;
	_toDiscard = nullptr;

	if (!_performer->pawn().position().hasResearchStation())
	{
		// Can only perform this action in a city with a research station
		std::cout << "No research station in this city.\n";
		return;
	}

	// Get city cards
	const auto& cards = _performer->cityCards();
	if (cards.empty())
	{
		// Can only perform this action if you have city cards to discard
		std::cout << "No city cards in hand.\n";
		return;
	}

	// List destinations
	const auto& cities = Board::instance().map().cities();

	_destination = 
		namedMenu(cities)
		.setMessage("Pick a destination:")
		.solicitInput();

	// List city cards in hand
	_toDiscard =
		namedMenu(cards)
		.setMessage("Pick a card to discard: ")
		.solicitInput();
}

void action::MoveFromResearchStation::perform()
{
	_performer->discard(*_toDiscard, Board::instance().playerDeck());
	_performer->moveTo(*_destination);
}

bool action::MoveFromResearchStation::isValid() const
{
	return _performer && _toDiscard && _destination;
}
