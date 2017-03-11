#pragma once

#include <memory>
#include <vector>

//#include "Card.h"

class Card;

template <typename T>
class Deck
{
	//static_assert(std::is_base_of<Card, T>::value, "A Deck must hold Cards.");

public:
	// Shuffles the draw pile
	void shuffleDeck();

	// huffles the draw pile
	void shuffleDiscards();

	// Prints the deck
	void printDeck();

	// True iff draw pile is empty
	bool empty() const;
	
	//Deck();
	//virtual ~Deck();
	//virtual void shuffleDeck(); //shuffles the actual deck
	//virtual void shuffleDiscards(); //shuffles the discard pile
	//virtual void printDeck();
	//virtual void addToDeck(std::unique_ptr<Card> cardToAdd); //this is so we can re-add the cards back to the deck
	//virtual void addToDiscard(std::unique_ptr<Card> cardToDiscard); //this is so we can discard the cards

	// Returns the top card of the deck
	std::unique_ptr<T> drawTopCard();
	// Returns the bottom card of the deck
	std::unique_ptr<T> drawBottomCard();
	// Inserts a card into the draw pile
	void addToDeck(std::unique_ptr<T> card);

	// Discards a card
	void addToDiscard(std::unique_ptr<T> card);

protected:
	std::vector<std::unique_ptr<T>> _drawPile;
	std::vector<std::unique_ptr<T>> _discardPile;
};