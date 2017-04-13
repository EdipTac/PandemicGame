#include "HandObserver.h"
#include "Board.h"

void forceDiscard(Player& player)
{
	const auto& cards = player.cards();
	std::cout << "You have " << cards.size() << " cards out of a maximum of 7. Pick a card to discard:\n";
	for (const auto& card : cards)
	{
		std::cout << "\t" << card->name() << "\n";
	}

	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(cards.begin(), cards.end(), [&](const auto& c)
		{
			return c->name() == input;
		});
		if (it != cards.end())
		{
			break;
		}
		std::cout << "Not a card in your hand.\n";
	}
	player.discard(input, Board::instance().playerDeck());
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
