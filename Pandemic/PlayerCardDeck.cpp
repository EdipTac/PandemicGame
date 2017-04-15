#include "PlayerCardDeck.h"

PlayerCardDeck::~PlayerCardDeck()
{}

TerminationState PlayerCardDeck::terminationState() const
{
	return empty() ? TerminationState::Defeat : TerminationState::InProgress;
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