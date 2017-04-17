#include "DirectFlight.h"
#include "Player.h"
#include "PlayerCityCard.h"
#include "Board.h"
#include "MenuUtils.h"

const std::string desc = "Discard a city card to move to the city named on the card.";

action::DirectFlight::DirectFlight(Player* const performer)
	: Action { "Direct Flight", desc, performer }
{}

void action::DirectFlight::solicitData()
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
		return;
	}

	// List cards, get player target, discard card, and move
	auto card =
		makeMenu(cards, [](const auto& card) { return card->name() + " " + colourName(card->colour()); })
		.setMessage("City cards: ")
		.solicitInput();
	if (card)
	{
		_target = &card->city();
	}
}

void action::DirectFlight::perform()
{
	_performer->discard(_target->name(), Board::instance().playerDeck());
	_performer->moveTo(*_target);
}

bool action::DirectFlight::isValid() const
{
	return _performer && _target;
}

void action::DirectFlight::setTarget(City* newTarget) {
	_target = newTarget;
}