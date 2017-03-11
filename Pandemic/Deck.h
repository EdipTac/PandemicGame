#pragma once

#include <ctime>
#include <iostream>
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

	// huffles the draw pile
	void shuffleDiscards();

	// Prints the deck
	void printDeck();

	// Returns the top card of the deck
	std::unique_ptr<T> drawCard();

	// Inserts a card into the draw pile
	void addToDeck(std::unique_ptr<T> cardToAdd);

	// Discards a card
	void addToDiscard(std::unique_ptr<T> cardToDiscard);

protected:
	std::vector<std::unique_ptr<T>> _drawPile;
	std::vector<std::unique_ptr<T>> _discardPile;
};