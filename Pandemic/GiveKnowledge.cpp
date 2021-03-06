#include <stdexcept>

#include "GiveKnowledge.h"
#include "Player.h"
#include "City.h"
#include "Board.h"
#include "MenuUtils.h"

const std::string desc =
	"GIVE the city card that matches the city you are in to another player. The other player "
	"must also be in the city with you. Both of you need to agree to do this. If the player who gets the card "
	"now has more than 7 cards, that player must immediately discard a card or play an Event card.";

action::GiveKnowledge::GiveKnowledge(Player* const performer)
	: Action { "Give Knowledge", desc, performer }
{}

void action::GiveKnowledge::solicitData()
{
	// Reset
	_target = nullptr;
	_card = nullptr;

	// Aliases
	const auto& position = _performer->pawn().position();
	const auto& players = Board::instance().players();

	// Do you have a city card matching your position to give?
	_card = _performer->positionCard();
	if (!_card)
	{
		std::cout << "You have no city card matching your position.\n";
		return;
	}

	// If so, select another player in your city
	std::vector<Player*> others;
	for (const auto& player : players)
	{
		if (player != _performer && player->pawn().position() == position)
		{
			others.push_back(player);
		}
	}

	// If there are none, you cannot give
	if (others.empty())
	{
		std::cout << "No other players in your city.\n";
		return;
	}

	// Select a player
	_target =
		namedMenu(others)
		.setMessage("Who to trade with? ")
		.solicitInput();
}

void action::GiveKnowledge::perform()
{
	_performer->giveCard(*_card, *_target);
}

bool action::GiveKnowledge::isValid() const
{
	return _performer && _card && _target;
}
