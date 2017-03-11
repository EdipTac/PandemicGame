#include "Deck.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm> //std::random_shuffle
Deck::~Deck() {}


void Deck::shuffleDeck() {
	std::vector < std::unique_ptr<Card> >temp;
	temp.reserve(deckOfCards.size());
	while (!deckOfCards.empty()) {
		int i = (rand()) % (deckOfCards.size());
		temp.push_back(std::move(deckOfCards[i]));
		deckOfCards.erase(deckOfCards.begin() + i);
	}
	deckOfCards = move(temp);
}

void Deck::shuffleDiscards() {
	std::vector < std::unique_ptr<Card> >temp;
	temp.reserve(discardDeck.size());
	while (!discardDeck.empty()) {
		int i = (rand()) % (discardDeck.size());
		temp.push_back(std::move(discardDeck[i]));
		discardDeck.erase(deckOfCards.begin() + i);
	}
	deckOfCards = move(temp);
}


//alternate implementation of shuffle
//void Deck::shuffleDeck() {
//	std::random_shuffle(deckOfCards.begin(), deckOfCards.end());
//}



 //the << deckofCards[i] seems to be an issue and wont compile
void Deck::printDeck() {
	std::cout << "The cards within the deck are as follows:\n" << std::endl;
	for (auto i = 0u; i < deckOfCards.size(); i++) {
		std::cout << deckOfCards[i]->name() << std::endl;
	}
}

std::unique_ptr<Card>  Deck::drawTopCard() {
	
	
	if (deckOfCards.size() != 0) {
		std::unique_ptr<Card> temp = move(deckOfCards[0]);
		deckOfCards.erase(deckOfCards.begin());
		return temp;

	}
	else {
		std::cout << "The deck is empty!" << std::endl;
		return NULL;
	}
}
std::unique_ptr<Card>  Deck::drawBottomCard() {


	if (deckOfCards.size() != 0) {
		std::unique_ptr<Card> temp = move(deckOfCards[deckOfCards.size()-1]);
		deckOfCards.erase(deckOfCards.end());
		return temp;

	}
	else {
		std::cout << "The deck is empty!" << std::endl;
		return NULL;
	}
}

void Deck::addToDeck(std::unique_ptr<Card> cardToAdd) {
	deckOfCards.push_back(move(cardToAdd));
}

void Deck::addToDiscard(std::unique_ptr<Card> cardToDiscard) {
	discardDeck.push_back(move(cardToDiscard));
}
