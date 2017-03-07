/*
InfectionDeckCard.cpp: .cpp source of InfectionDeckCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/
#include <iostream>
#include "InfectionCardDeck.h"
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

InfectionCardDeck::InfectionCardDeck(string fileName) {
	// initiate 48 infection cards on deck
	auto  map = readMapFromFile(fileName);

	for (const auto& city : map->cities())
	{
		deck.push_back(std::make_unique<InfectionCard>(*city));
	}

    shuffle(deck);// shuffle infection cards on deck/
}
void InfectionCardDeck::shuffle(vector <InfectionCard>& cards) {
	 
	std::random_shuffle(cards.begin(), cards.end());
	 
	}


InfectionCardDeck::~InfectionCardDeck() {

}

void InfectionCardDeck::print() {
	for (const auto& infectionCard : deck) {
	   cout << "Infection cards on deck : " << infectionCard.getCityName() <<" with the colour of: " << colourAbbreviation(infectionCard.getCityColour()) <<endl;
	}
}
void InfectionCardDeck::checkInfectionCardHistory() {
	for (const auto& infectionCard : discardPile) {
		cout << "Infection cards on discard pile: " << infectionCard.getCityName() << " with the colour of: " << colourAbbreviation(infectionCard.getCityColour()) << endl;
	}
}
void InfectionCardDeck::flipInfectionCard(CubePool& pool) {
	if (deck.size() < 1) {
		cout << "There is no more infection cards to draw " << endl;

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
	if (outbreakMarker = 5) {
		cout << "Outbreak tracker reaches the last space, the game is over. " << endl;
		system("pause");
		system(0);
	}
	outbreakMarker++;
	infectionRate = outbreakTracker[outbreakMarker];
}
void InfectionCardDeck::pullBottomInfectionCard(CubePool& pool) {
	(deck[0].getCity()).addDiseaseCubes(deck[0].getCityColour(), CUBE_EPIDEMIC_INFECTION, pool, *this);
	discardPile.push_back(deck[0]);
    deck.erase(deck.begin());
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
