#include "PlayerCardDeck.h"

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

void PlayerCardDeck::addEpidemicToDeck(std::unique_ptr<EpidemicCard> card, size_t index, size_t numEpidemic)
{
	_drawPile.insert(_drawPile.begin() + index + (_drawPile.size() / numEpidemic), (move(card)));
}
