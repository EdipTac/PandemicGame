#include "InfectionCardDeck.h"

InfectionCardDeck::~InfectionCardDeck() {}

TerminationState InfectionCardDeck::terminationState() const
{
	return empty() ? TerminationState::Defeat : TerminationState::InProgress;
}

std::unique_ptr<InfectionCard> InfectionCardDeck::drawTopCard()
{
	auto card = Deck<InfectionCard>::drawTopCard();
	notify();
	return card;
}
