#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

#include "Deck.h"
#include "PlayerCard.h"
#include "InfectionCard.h"

size_t randSize(size_t max);
template <typename T> void shuffle(std::vector<std::unique_ptr<T>>& cards);

template <typename T>
void Deck<T>::shuffleDeck()
{
	shuffle(_drawPile);
}

template <typename T>
void Deck<T>::shuffleDiscards()
{
	shuffle(_discardPile);
}


template <typename T>
void Deck<T>::printDeck()
{
	std::cout << "The cards within the deck are as follows:\n" << std::endl;
	for (auto i = 0u; i < _drawPile.size(); i++)
	{
		std::cout << _drawPile[i]->name() << std::endl;
	}
}

template <typename T>
std::unique_ptr<T> Deck<T>::drawCard()
{
	if (_drawPile.empty())
	{
		throw std::logic_error { "Trying to draw from an empty deck." };
	}

	auto temp = move(_drawPile.back());
	_drawPile.pop_back();
	return temp;
}

template <typename T>
void Deck<T>::addToDeck(std::unique_ptr<T> card)
{
	_drawPile.push_back(move(card));
}

template <typename T>
void Deck<T>::addToDiscard(std::unique_ptr<T> card)
{
	_discardPile.push_back(move(card));
}

template class Deck<PlayerCard>;
template class Deck<InfectionCard>;

size_t randSize(size_t max)
{
	static std::mt19937 gen { std::random_device {}() };
	static std::uniform_int_distribution<size_t> dis;
	dis.param(std::uniform_int_distribution<size_t>::param_type { 0, max });
	return dis(gen);
}

template <typename T>
void shuffle(std::vector<std::unique_ptr<T>>& cards)
{
	std::vector<std::unique_ptr<T>> temp;
	temp.reserve(cards.size());
	while (!cards.empty())
	{
		const auto i = randSize(cards.size());
		temp.push_back(std::move(cards[i]));
		cards.erase(cards.begin() + i);
	}
	cards = std::move(temp);
}
