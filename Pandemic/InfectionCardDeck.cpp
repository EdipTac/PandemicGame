#include "InfectionCardDeck.h"

InfectionCardDeck::~InfectionCardDeck() {}

TerminationState InfectionCardDeck::terminationState() const
{
	return empty() ? TerminationState::Defeat : TerminationState::InProgress;
}
