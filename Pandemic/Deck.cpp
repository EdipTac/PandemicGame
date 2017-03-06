#include "Deck.h"



Deck::~Deck() {}

//EDIP -- fix this.
//void Deck::shuffleDeck() {
//	srand(time(0));
//	int index;
//	Card* temp; //we need to make a copy constructor for Card
//	for (unsigned int i = 0; i < deckOfCards.size(); i++) {
//		index = rand() % deckOfCards.size();
//		temp = deckOfCards[i];
//		deckOfCards[i] = deckOfCards[index];
//		deckOfCards[index] = temp;
//	}
//
//}
//
//void Deck::printDeck(std::vector<Card*> deckToPrint) {
//	std::cout << "The cards within the deck are as follows:\n" << std::endl;
//	for (unsigned int i = 0; i < deckToPrint.size(); i++) {
//		std::cout << deckToPrint[i] << std::endl;
//	}
//}
//
//std::unique_ptr<Card*>  Deck::drawCard(std::vector <Card*> deckToDrawFrom) {
//	
//	
//	if (deckToDrawFrom.size() != 0) {
//		auto temp = (*(deckToDrawFrom[0]));
//		deckToDrawFrom.erase(deckToDrawFrom[0]);
//		return temp;
//
//	}
//	else {
//		std::cout << "The deck is empty!" << std::endl;
//		return NULL;
//	}
//}