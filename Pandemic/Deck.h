#pragma once

#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

#include "Card.h"

template <typename T>
class Deck
{
	static_assert(std::is_base_of<Card, T>::value, "A Deck must hold Cards");

public:
	void shuffleDeck(); //shuffles the actual deck
	void shuffleDiscards(); //shuffles the discard pile
	void printDeck();
	std::unique_ptr<T> drawCard(); //this is to draw a card from the top of the deck
	void addToDeck(std::unique_ptr<T> cardToAdd); //this is so we can re-add the cards back to the deck
	void addToDiscard(std::unique_ptr<T> cardToDiscard); //this is so we can discard the cards

protected:
	std::vector<std::unique_ptr<T>> deckOfCards; //deck of our actual cards
	std::vector<std::unique_ptr<T>> discardDeck;//the respective discard pile for our deck
};