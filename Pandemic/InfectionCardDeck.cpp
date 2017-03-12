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
		Deck<InfectionCard>::addToDeck(std::make_unique<InfectionCard>(*city));
	}

	Deck<InfectionCard>::shuffleDeck();// shuffle infection cards on deck/
}
#pragma warning (push)
#pragma warning (disable: 4100) // S since cards isn't used
void InfectionCardDeck::shuffle(std::vector <std::unique_ptr<InfectionCard>>& cards) {
	// Won't compile
	//std::random_shuffle(cards.begin(), cards.end());
	 
	}
#pragma warning (pop)

InfectionCardDeck::~InfectionCardDeck() {

}

void InfectionCardDeck::checkInfectionCardHistory() {
	for (const auto& infectionCard : _discardPile) {
		std::cout << "Infection cards on discard pile: " << infectionCard->name() << " with the colour of: " << colourAbbreviation(infectionCard->colour()) << std::endl;
	}
}
void InfectionCardDeck::flipInfectionCard(CubePool& pool) {
	if (_drawPile.size() < 1) {
		std::cout << "There is no more infection cards to draw " << std::endl;

	}
	else {

		auto temp = std::move(_drawPile[_drawPile.size() -1]);
		(temp->city()).addDiseaseCubes(temp->colour(), CUBE_NORMAL_INFECTION, pool, *this);
		_drawPile.pop_back();
		_drawPile.shrink_to_fit();
		_discardPile.push_back(move(temp));

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

void InfectionCardDeck::pullBottomInfectionCard(CubePool& pool) {
	(_drawPile[0]->city()).addDiseaseCubes(_drawPile[0]->colour(), CUBE_EPIDEMIC_INFECTION, pool, *this);
	_discardPile.push_back(std::move(_drawPile[0]));
	_drawPile[0].reset(nullptr);
	_drawPile.erase(_drawPile.begin());
	_drawPile.shrink_to_fit();

}
void InfectionCardDeck::reshuffleAndputback() {
	shuffle(_discardPile);
	const auto k = _discardPile.size();
	for (auto i = 0; i < k; i++) {
		_drawPile.push_back(std::move(_discardPile[i]));
	}
	_discardPile.clear();
}
