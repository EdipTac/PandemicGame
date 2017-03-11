/*
InfectionDeckCard.cpp: .cpp source of InfectionDeckCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/


#include <ctime>
#include <iostream>
#include <string>

#include "InfectionCardDeck.h"

InfectionCardDeck::InfectionCardDeck(std::string fileName)
{
	// initiate 48 infection cards on deck
	auto  map = readMapFromFile(fileName);

	for (const auto& city : map->cities())
	{
		addToDeck(std::make_unique<InfectionCard>(*city));
	}

    shuffleDeck();// shuffle infection cards on deck/
}
#pragma warning (push)
#pragma warning (disable: 4100) // S since cards isn't used

#pragma warning (pop)

InfectionCardDeck::~InfectionCardDeck() {

}

void InfectionCardDeck::printDeck() {
	for (const auto& infectionCard : deckOfCards) {
		std::cout << "Infection cards on deck : " << infectionCard->description() << std::endl;
	}
}
void InfectionCardDeck::checkInfectionCardHistory() {
	for (const auto& infectionCard : discardDeck) {
		std::cout << "Infection cards on discard pile: " << infectionCard->description()<< std::endl;
	}
	}



void InfectionCardDeck::reshuffleAndputback() {
	shuffleDiscards();
	for ( const auto& infectionCard : discardDeck ) {
		deckOfCards.push_back(move(infectionCard));
	}
	discardDeck.clear();
}
