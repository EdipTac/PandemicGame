#include "TakeKnowledge.h"
#include "Player.h"
#include "City.h"
#include "Board.h"

const std::string desc =
	"TAKE a city card that matches the city you are in from another player. The other player "
	"must also be in the city with you. Both of you need to agree to do this. If the player who gets the card "
	"now has more than 7 cards, that player must immediately discard a card or play an Event card.";

action::TakeKnowledge::TakeKnowledge(Player* const performer)
	: Action { "Take Knowledge", desc, performer }
{}

void action::TakeKnowledge::solicitData()
{
	// Aliases
	const auto& position = _performer->pawn().position();
	const auto& players = Board::instance().players();

	// Get other people in the city with a matching city card
	std::vector<Player*> others;
	for (const auto& player : players)
	{
		if (player != _performer
			&& player->pawn().position() == position
			&& player->positionCard())
		{
			others.push_back(player);
		}
	}

	// If there are none, you cannot take
	if (others.empty())
	{
		std::cout << "No other players with a matching city card in your city.\n";
		return;
	}

	// Select a player
	std::cout << "Who to trade with?\n";
	for (const auto& player : others)
	{
		std::cout << "\t" << player->name() << "\n";
	}
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
			_target = *it;
			break;
		}
		std::cout << "Not a player in this city.\n";
	}

	// Prepare their city card for transfer
	_card = _target->positionCard();
}

void action::TakeKnowledge::perform()
{
	_target->giveCard(*_card, *_performer);
}

bool action::TakeKnowledge::isValid() const
{
	return _performer && _card && _target;
}
