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
	virtual void shuffleDeck();

	// shuffles the draw pile
	virtual void shuffleDiscards();

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
	virtual std::unique_ptr<T> drawTopCard();

	// Returns the top card of the discard deck
	virtual std::unique_ptr<T> drawTopDiscard();

	// Returns the bottom card of the active deck
	virtual std::unique_ptr<T> drawBottomCard();

	// Returns the bottom card of the discard deck
	virtual std::unique_ptr<T> drawBottomDiscard();

	// Inserts a card into the draw pile
	virtual void addToDeck(std::unique_ptr<T> card);

	// Discards a card
	virtual void addToDiscard(std::unique_ptr<T> card);

	// deletes a discarded card
	virtual void deleteDiscard();
	
	virtual void deleteDiscard(std::string cardToDelete);

protected:
	std::vector<std::unique_ptr<T>> _drawPile;
	std::vector<std::unique_ptr<T>> _discardPile;
};