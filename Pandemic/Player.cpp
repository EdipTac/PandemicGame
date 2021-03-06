#pragma once

#include <sstream>

#include "Pawn.h"
#include "Player.h"
#include "PlayerCityCard.h"
#include "Board.h"
#include "EventCard.h"

// Default Constructor
Player::Player()
	: _pawn { *this }
{}

// Constructor
Player::Player(const std::string name, const Pawn& pawn, std::vector<std::unique_ptr<PlayerCard>>& cards, std::unique_ptr<RoleCard> role)
	: _name { name }
	, _pawn { pawn }
	, _cards { std::move(cards) }
	, _role { std::move(role) }
	, _oneQuietNight {false}
{}

std::string Player::name() const
{
	return _name;
}

// Accessors and Mutators
std::vector<PlayerCard*> Player::cards() const
{
	std::vector<PlayerCard*> cardView;
	for (const auto& card : _cards)
	{
		cardView.push_back(card.get());
	}
	return cardView;
}

size_t Player::cardCount() const
{
	return _cards.size();
}

void Player::addCard(std::unique_ptr<PlayerCard> card) {
	_cards.push_back(std::move(card));
	notify();
}

void Player::drawFrom(Deck<PlayerCard>& deck, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		auto card = deck.drawTopCard();
		if (!card)
		{
			// Dick was empty, so card pointer is null
			break;
		}
		card->onDraw();
		card->cardWork(Board::instance().infectionDeck());
		if (card->isHandCard())
		{
			_cards.push_back(std::move(card));
		}
		else
		{
			deck.addToDiscard(std::move(card));
		}
	}
	notify();
}

PlayerCard* Player::getCard(const std::string& name)
{
	auto it = std::find_if(_cards.begin(), _cards.end(), [&](const auto& card)
	{
		return card->name() == name;
	});
	if (it == _cards.end())
	{
		return nullptr;
	}
	return it->get();
}

void Player::discard(PlayerCard& card, Deck<PlayerCard>& deck)
{
	// Find card in hand
	const auto& it = std::find_if(_cards.begin(), _cards.end(), [&](const auto& c)
	{
		return c.get() == &card;
	});
	if (it == _cards.end())
	{
		// Not found
		return;
	}
	deck.addToDiscard(std::move(*it));
	_cards.erase(it);
}

void Player::discard(const std::string& name, Deck<PlayerCard>& deck)
{
	discard(*getCard(name), deck);
}

std::ostream& operator<<(std::ostream& os, PlayerCard& card)
{
	return os << card.string();
}

void Player::displayCards()
{
	size_t maxLength = 0;
	for (const auto& card : _cards)
	{
		maxLength = std::max(maxLength, card->rawString().size());
	}
	std::stringstream ss;
	ss << "\nHand:\n";
	for (const auto& card : _cards)
	{
		ss << "  " << card->string(maxLength + 2 - card->rawString().size()) << "\n";
	}
	ss << "\n";
	std::cout << ss.str();
}

bool Player::hasPositionCard()
{
	auto& position = _pawn.position();
	for (const auto& card : cityCards())
	{
		if (card->city() == position)
		{
			return true;
		}
	}
	return false;
}

PlayerCard* Player::positionCard()
{
	auto& position = _pawn.position();
	const auto& isPositionCard = [&](const auto& card)
	{
		return card->city() == position;
	};
	const auto& cards = cityCards();
	const auto& it = std::find_if(cards.begin(), cards.end(), isPositionCard);
	return it == cards.end() ? nullptr : *it;
}

void Player::giveCard(const PlayerCard& card, Player& recipient)
{
	const auto& it = std::find_if(_cards.begin(), _cards.end(), [&](const auto& c)
	{
		return c.get() == &card;
	});
	if (it == _cards.end())
	{
		return;
	}
	auto donation = std::move(*it);
	_cards.erase(it);
	recipient.addCard(std::move(donation));
}

void Player::moveTo(City& destination)
{
	_pawn.position().onExit(*this);
	_pawn.setPosition(destination);
	_pawn.position().onEnter(*this);
}

std::vector<PlayerCityCard*> Player::cityCards() const
{
	std::vector<PlayerCityCard*> view;
	for (const auto& card : _cards)
	{
		if (card->type() == PlayerCardType::CityCard)
		{
			view.push_back(static_cast<PlayerCityCard*>(card.get()));
		}
	}
	return view;
}

std::vector<EventCard*> Player::eventCards() const
{
	std::vector<EventCard*> view;
	for (const auto& card : _cards)
	{
		if (card->isEventCard())
		{
			view.push_back(static_cast<EventCard*>(card.get()));
		}
	}
	return view;
}

Pawn& Player::pawn()
{
	return _pawn;
}

const RoleCard& Player::role() const
{
	return *_role;
}

void Player::setRole(std::unique_ptr<RoleCard> role)
{
	_role = std::move(role);
}

std::string Player::getName() const {
	return _name;
}
void Player::setName(const std::string name) {
	this->_name = name;
}

void Player::displayRole() {
	_role->print();
}

bool Player::isOneQuietNight() {
	return _oneQuietNight;
}

void Player::setOneQuietNight(bool boolean) {
	_oneQuietNight = boolean;
}
