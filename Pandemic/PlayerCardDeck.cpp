#include <algorithm>

#include "PlayerCardDeck.h"
#include "Util.h"

PlayerCardDeck::~PlayerCardDeck() {}

TerminationState PlayerCardDeck::terminationState() const
{
	return empty() ? TerminationState::Defeat : TerminationState::InProgress;
}

std::string PlayerCardDeck::message() const
{
	return "No cards left to draw.";
}

std::unique_ptr<PlayerCard> PlayerCardDeck::drawTopCard()
{
	notify();
	if (empty())
	{
		// Game over; but need to return something
		return {};
	}
	return Deck<PlayerCard>::drawTopCard();
}


void PlayerCardDeck::addEpidemicCards(const size_t count)
{
	std::vector<std::unique_ptr<PlayerCard>> newDrawPile;
	const size_t subDeckSize = std::max(_drawPile.size() / count, 1ull);
	
	// For each epidemic card, make a subdeck with one epidemic card
	for (size_t i = 0; i < count; ++i)
	{
		std::vector<std::unique_ptr<PlayerCard>> subDeck;
		
		// Grab subDeckSize cards from draw pile
		for (size_t j = 0; j < subDeckSize; ++j)
		{
			if (!_drawPile.empty())
			{
				subDeck.push_back(std::move(_drawPile.back()));
				_drawPile.pop_back();
			}
		}
		
		// Add an epidemic card
		subDeck.push_back(std::make_unique<EpidemicCard>());

		// Shuffle subdeck
		shuffle(subDeck);

		// Add to new draw pile
		while (!subDeck.empty())
		{
			newDrawPile.push_back(std::move(subDeck.back()));
			subDeck.pop_back();
		}
	}

	// Assign to draw pile
	_drawPile = std::move(newDrawPile);
}
