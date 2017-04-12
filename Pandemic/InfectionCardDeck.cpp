/*
InfectionDeckCard.cpp: .cpp source of InfectionDeckCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/


#include <ctime>
#include <iostream>
#include <string>

#include "InfectionCardDeck.h"

InfectionCardDeck::InfectionCardDeck() {
}

InfectionCardDeck::InfectionCardDeck(std::string fileName)
{
   // initiate 48 infection cards on deck
	for (const auto& city : Board::instance().map().cities())
	{
      Deck<InfectionCard>::addToDeck(std::make_unique<InfectionCard>(*city));
   }
	shuffleDeck();// shuffle infection cards on deck/
}

#pragma warning (push)

#pragma warning (disable: 4100) // S since cards isn't used

#pragma warning (pop)
InfectionCardDeck::~InfectionCardDeck() {

}

void InfectionCardDeck::printDeck() {
	for (const auto& infectionCard : _drawPile) {
		std::cout << "Infection cards on deck : " << infectionCard->description() << std::endl;
	}
}

void InfectionCardDeck::checkInfectionCardHistory() {
	for (const auto& infectionCard : _discardPile) {
		std::cout << "Infection cards on discard pile: " << infectionCard->description() << std::endl;
	}
}


void InfectionCardDeck::reshuffleAndputback() {
	shuffleDiscards();
	for (auto& infectionCard : _discardPile) {
		Deck<InfectionCard>::addToDeck(std::move(infectionCard));
	}
	_discardPile.clear();

}

