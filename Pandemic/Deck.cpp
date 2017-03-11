#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

#include "Deck.h"
#include "PlayerCard.h"
#include "InfectionCard.h"

template <typename T>
void Deck<T>::shuffleDeck()
{
	std::vector<std::unique_ptr<T>> temp;
	temp.reserve(deckOfCards.size());
	while (!deckOfCards.empty())
	{
		int i = (rand()) % (deckOfCards.size());
		temp.push_back(std::move(deckOfCards[i]));
		deckOfCards.erase(deckOfCards.begin() + i);
	}
	deckOfCards = move(temp);
}

template <typename T>
void Deck<T>::shuffleDiscards()
{
	std::vector<std::unique_ptr<T>> temp;
	temp.reserve(discardDeck.size());
	while (!discardDeck.empty())
	{
		int i = (rand()) % (discardDeck.size());
		temp.push_back(std::move(discardDeck[i]));
		discardDeck.erase(deckOfCards.begin() + i);
	}
	deckOfCards = move(temp);
}


template <typename T>
void Deck<T>::printDeck() {
	std::cout << "The cards within the deck are as follows:\n" << std::endl;
	for (auto i = 0u; i < deckOfCards.size(); i++)
	{
		std::cout << deckOfCards[i]->name() << std::endl;
	}
}

template <typename T>
std::unique_ptr<T> Deck<T>::drawCard()
{
	if (deckOfCards.size() != 0)
	{
		std::unique_ptr<T> temp = move(deckOfCards[0]);
		deckOfCards.erase(deckOfCards.begin());
		return temp;

	}
	else
	{
		std::cout << "The deck is empty!" << std::endl;
		return NULL;
	}
}

template <typename T>
void Deck<T>::addToDeck(std::unique_ptr<T> cardToAdd)
{
	deckOfCards.push_back(move(cardToAdd));
}

template <typename T>
void Deck<T>::addToDiscard(std::unique_ptr<T> cardToDiscard)
{
	discardDeck.push_back(move(cardToDiscard));
}

template class Deck<PlayerCard>;
template class Deck<InfectionCard>;
