#include "PlayerCardDeck.h"

PlayerCardDeck::~PlayerCardDeck()
{}

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