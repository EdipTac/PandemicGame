#pragma once

#include <memory>
#include <vector>

#include "Card.h"

template <typename T>
class Deck
{
	static_assert(std::is_base_of<Card, T>::value, "A Deck must hold Cards.");

public:
	// Shuffles the draw pile
	void shuffleDeck();

	// shuffles the draw pile
	void shuffleDiscards();

	std::vector<T*> drawPile() const;

	std::vector<T*> discardPile() const;

	// Prints the deck
	void printDeck();

	// True iff draw pile is empty
	bool empty() const;

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