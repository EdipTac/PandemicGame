#include <sstream>

#include "HandObserver.h"
#include "Board.h"
#include "MenuUtils.h"

void forceDiscard(Player& player)
{
	const auto& cards = player.cards();
	const std::string msg = "You have " + std::to_string(cards.size()) + " cards out of a maximum of 7.\n"
							 + "You must discard " + std::to_string(cards.size() - 7) + ". Pick a card to discard:\n";

	auto card =
		namedMenu(cards, false) // Not optional - must discard!
		.setMessage(msg)
		.solicitInput();

	player.discard(*card, Board::instance().playerDeck());
}

HandObserver::~HandObserver() {}

void HandObserver::update()
{
	for (const auto& player : _subjects)
	{
		while (player->cardCount() > 7)
		{
			forceDiscard(*player);
		}
	}
}
