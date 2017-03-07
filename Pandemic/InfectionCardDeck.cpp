/*
InfectionDeckCard.cpp: .cpp source of InfectionDeckCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>

#include "InfectionCardDeck.h"

InfectionCardDeck::InfectionCardDeck(std::string fileName)
{
	// initiate 48 infection cards on deck
	auto map = readMapFromFile(fileName);

	for (const auto& city : map->cities())
	{
		deck.push_back(InfectionCard(*city));
	}

    shuffle(deck);// shuffle infection cards on deck/
}
#pragma warning (push)
#pragma warning (disable: 4100) // S since cards isn't used
void InfectionCardDeck::shuffle(std::vector <InfectionCard>& cards) {
	// Won't compile
	//std::random_shuffle(cards.begin(), cards.end());
	 
	}
#pragma warning (pop)

InfectionCardDeck::~InfectionCardDeck() {

}

void InfectionCardDeck::print() {
	for (const auto& infectionCard : deck) {
		std::cout << "Infection cards on deck : " << infectionCard.getCityName() <<" with the colour of: " << colourAbbreviation(infectionCard.getCityColour()) << std::endl;
	}
}
void InfectionCardDeck::checkInfectionCardHistory() {
	for (const auto& infectionCard : discardPile) {
		std::cout << "Infection cards on discard pile: " << infectionCard.getCityName() << " with the colour of: " << colourAbbreviation(infectionCard.getCityColour()) << std::endl;
	}
}
void InfectionCardDeck::flipInfectionCard(CubePool& pool) {
	if (deck.size() < 1) {
		std::cout << "There is no more infection cards to draw " << std::endl;

	}
	else {

		InfectionCard temp = deck[deck.size() -1];
		(temp.getCity()).addDiseaseCubes(temp.getCityColour(), CUBE_NORMAL_INFECTION, pool, *this);
		deck.pop_back();
		deck.shrink_to_fit();
		discardPile.push_back(temp);

	}
}
int InfectionCardDeck::getInfectionRate() {
	return infectionRate;
}
void InfectionCardDeck::moveOutbreakMarker() {
	if (outbreakMarker == 5) {
		std::cout << "Outbreak tracker reaches the last space, the game is over. " << std::endl;
		system("pause");
		system(0);
	}
	outbreakMarker++;
	infectionRate = outbreakTracker[outbreakMarker];
}

// Use pointers!
void InfectionCardDeck::pullBottomInfectionCard(CubePool& pool) {
	(deck[0].getCity()).addDiseaseCubes(deck[0].getCityColour(), CUBE_EPIDEMIC_INFECTION, pool, *this);
	discardPile.push_back(deck[0]);
	// Won't compile
    //deck.erase(deck.begin());
	deck.shrink_to_fit();

}
void InfectionCardDeck::reshuffleAndputback() {
	shuffle(discardPile);
	const auto k = discardPile.size();
	for (auto i = 0; i < k; i++) {
		deck.push_back(discardPile[i]);
	}
	discardPile.clear();
}
