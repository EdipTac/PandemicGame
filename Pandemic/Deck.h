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

	//prints the DiscardDeck
	void printDiscards();

	// True iff draw pile is empty
	bool empty() const;

	// True iff discard pile is empty
	bool emptyDiscard() const;

	// Returns the top card of the active deck
	std::unique_ptr<T> drawTopCard();

	// Returns the top card of the discard deck
	std::unique_ptr<T> drawTopDiscard();


	// Returns the bottom card of the active deck
	std::unique_ptr<T> drawBottomCard();

	// Returns the bottom card of the discard deck
	std::unique_ptr<T> drawBottomDiscard();

	// Inserts a card into the draw pile
	void addToDeck(std::unique_ptr<T> card);

	// Discards a card
	void addToDiscard(std::unique_ptr<T> card);

	// deletes a discarded card
	void deleteDiscard();
	
	void deleteDiscard(std::string cardToDelete);



protected:
	std::vector<std::unique_ptr<T>> _drawPile;
	std::vector<std::unique_ptr<T>> _discardPile;
};