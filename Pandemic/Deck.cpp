#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "Deck.h"
#include "PlayerCard.h"
#include "InfectionCard.h"

size_t randSize(size_t max);

template <typename T>
void Deck<T>::shuffleDeck()
{
	std::vector<std::unique_ptr<T>> temp;
	temp.reserve(_drawPile.size());
	while (!_drawPile.empty())
	{
		const auto i = randSize(_drawPile.size());
		temp.push_back(std::move(_drawPile[i]));
		_drawPile.erase(_drawPile.begin() + i);
	}
	_drawPile = std::move(temp);
}

template <typename T>
void Deck<T>::shuffleDiscards()
{
	std::vector<std::unique_ptr<T>> temp;
	temp.reserve(_discardPile.size());
	while (!_discardPile.empty())
	{
		int i = (rand()) % (_discardPile.size());
		temp.push_back(std::move(_discardPile[i]));
		_discardPile.erase(_drawPile.begin() + i);
	}
	_drawPile = move(temp);
}


template <typename T>
void Deck<T>::printDeck() {
	std::cout << "The cards within the deck are as follows:\n" << std::endl;
	for (auto i = 0u; i < _drawPile.size(); i++)
	{
		std::cout << _drawPile[i]->name() << std::endl;
	}
}

template <typename T>
std::unique_ptr<T> Deck<T>::drawCard()
{
	if (_drawPile.size() != 0)
	{
		std::unique_ptr<T> temp = move(_drawPile[0]);
		_drawPile.erase(_drawPile.begin());
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
	_drawPile.push_back(move(cardToAdd));
}

template <typename T>
void Deck<T>::addToDiscard(std::unique_ptr<T> cardToDiscard)
{
	_discardPile.push_back(move(cardToDiscard));
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
