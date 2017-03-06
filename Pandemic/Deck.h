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
	virtual void shuffleDeck();
	virtual void printDeck();
	virtual std::unique_ptr<Card*> drawCard();


protected:
	std::vector<std::unique_ptr<Card>> deckOfCards;
	std::unique_ptr<Card*> discardDeck;
	

};