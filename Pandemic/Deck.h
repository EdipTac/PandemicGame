#pragma once

#include <memory>
#include <vector>
#include "Card.h"
#include <ctime>
#include <iostream>

class Deck {

public:
	
	Deck();
	Deck(Card& card);
	virtual ~Deck();
	virtual void shuffleDeck(std::vector <Card*> deckToShuffle);
	virtual void printDeck(std::vector <Card*> deckToPrint);
	virtual std::unique_ptr<Card*> drawCard(std::vector<Card*> deckToDrawFrom);


protected:
	std::unique_ptr<Card*> deckOfCards;
	std::unique_ptr<Card*> discardDeck;
	

};