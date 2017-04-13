/*
InfectionDeckCard.cpp: .cpp source of InfectionDeckCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/


#include <ctime>
#include <iostream>
#include <string>

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
