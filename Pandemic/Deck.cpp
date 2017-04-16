#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

#include "Deck.h"
#include "PlayerCard.h"
#include "InfectionCard.h"
#include "RoleCard.h"
#include "Util.h"

template class Deck<PlayerCard>;
template class Deck<InfectionCard>;
template class Deck<RoleCard>;

size_t randSize(const size_t max);
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

template<typename T>
std::vector<T*> Deck<T>::drawPile() const
{
	std::vector<T*> cards;
	for (const auto& card : _drawPile)
	{
		cards.push_back(card.get());
	}
	return cards;
}

template<typename T>
std::vector<T*> Deck<T>::discardPile() const
{
	std::vector<T*> cards;
	for (const auto& card : _discardPile)
	{
		cards.push_back(card.get());
	}
	return cards;
}


template <typename T>
void Deck<T>::printDeck()
{
	std::cout << "The cards within the deck are as follows:\n";
	for (auto i = 0u; i < _drawPile.size(); i++)
	{
		std::cout << _drawPile[i]->name() << std::endl;
	}
}

template <typename T>
void Deck<T>::printDiscards()
{
	std::cout << "The cards within the discard pile are as follows: \n";
	for (auto i = 0u; i < _discardPile.size(); i++) 
	{
		std::cout << _discardPile[i]->name() << std::endl;
	}
}

template<typename T>
bool Deck<T>::empty() const
{
	return _drawPile.empty();
}

template<typename T>
bool Deck<T>::emptyDiscard() const
{
	return _discardPile.empty();
}

template <typename T>
std::unique_ptr<T> Deck<T>::drawTopCard()
{
	if (_drawPile.empty())
	{
		throw std::logic_error { "Trying to draw from an empty deck." };
	}

	auto temp = std::move(_drawPile.back());
	//_discardPile.push_back(move(temp)); should put used card to discard pile, but not compile
	_drawPile.pop_back();
	return temp;
}
template <typename T>
std::unique_ptr<T> Deck<T>::drawTopDiscard()
{
	if (_discardPile.empty())
	{
		throw std::logic_error{ "Trying to draw from an empty discard deck." };
	}

	auto temp = std::move(_discardPile.back());
	_discardPile.pop_back();
	return temp;
}

template <typename T>
std::unique_ptr<T> Deck<T>::drawBottomCard()
{
	if (_drawPile.empty())
	{
		throw std::logic_error { "Trying to draw from an empty deck." };
	}

	auto temp = std::move(_drawPile.front());
	_drawPile.erase(_drawPile.begin());
	return temp;
}

template <typename T>
std::unique_ptr<T> Deck<T>::drawBottomDiscard()
{
	if (_discardPile.empty())
	{
		throw std::logic_error{ "Trying to draw from an empty discard deck." };
	}

	auto temp = std::move(_discardPile.front());
	_discardPile.erase(_discardPile.begin());
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

size_t randSize(const size_t max)
{
	static std::mt19937 gen { std::random_device {}() };
	static std::uniform_int_distribution<size_t> dis;
	dis.param(std::uniform_int_distribution<size_t>::param_type { 0, max - 1 });
	return dis(gen);
}

template <typename T>
void Deck<T>::deleteDiscard()
{
	if (_discardPile.empty())
	{
		throw std::logic_error{ "There are no cards in the discard pile." };
	}
	std::cout << "Please enter the name of the card you would like to delete.\n";
	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(_discardPile.begin(), _discardPile.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != _discardPile.end())
		{
			_discardPile.erase(it);
			break;
		}
		std::cout << "No card by that name in the discard pile.\n";

	}
}

template <typename T>
void Deck<T>::deleteDiscard(std::string cardToDelete)
{
	if (_discardPile.empty())
	{
		throw std::logic_error{ "There are no cards in the discard pile." };
	}
	const auto& it = std::find_if(_discardPile.begin(), _discardPile.end(), [&](const auto& c)
	{
		return cardToDelete == c->name();
	});
	if (it != _discardPile.end())
	{
		_discardPile.erase(it);
		return;
	}

}
