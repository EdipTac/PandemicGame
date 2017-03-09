#pragma once

#include <memory>
#include <vector>
#include "Card.h"
#include <ctime>
#include <iostream>

class Deck {

public:
	
	Deck();
	virtual ~Deck();
	virtual void shuffleDeck(); //shuffles the actual deck
	virtual void shuffleDiscards(); //shuffles the discard pile
	//virtual void printDeck();
	virtual std::unique_ptr<Card> drawCard(); //this is to draw a card from the top of the deck
	virtual void addToDeck(std::unique_ptr<Card> cardToAdd); //this is so we can re-add the cards back to the deck
	virtual void addToDiscard(std::unique_ptr<Card> cardToDiscard); //this is so we can discard the cards


protected:
	std::vector<std::unique_ptr<Card>> deckOfCards; //deck of our actual cards
	std::vector<std::unique_ptr<Card>> discardDeck;//the respective discard pile for our deck
	

};