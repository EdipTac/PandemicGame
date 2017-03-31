#pragma once

#include "Pawn.h"
#include "Player.h"
#include "PlayerCityCard.h"
#include "Board.h"

// Default Constructor
Player::Player()
	: _pawn { *this }
	, _role { std::make_unique<RoleCard>() }
{}

// Constructor
Player::Player(const std::string name, const Pawn& pawn, std::vector<std::unique_ptr<PlayerCard>>& cards, std::unique_ptr<RoleCard> role)
	: _name { name }
	, _pawn { pawn }
	, _cards { std::move(cards) }
	, _role { std::move(role) }
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
void Player::addCard(std::unique_ptr<PlayerCard> card) {
	_cards.push_back(std::move(card));
}
// Should return to deck!
void Player::removeCardByName(const std::string& name)
{
	auto it = std::find_if(_cards.begin(), _cards.end(), [&](const auto& card) { return card->name() == name; });
	if (it == _cards.end())
	{
		return;
	}
	_cards.erase(it);
}

std::ostream& operator<<(std::ostream& os, PlayerCard& card)
{
	return os << card.toString();
}

void Player::displayCards() {
	std::cout << "\nDisplaying Cards on hand: \n";
	int k = 0;
	for (auto& card : cityCards()) {
		std::cout << card->toString() << "\n";
		k++;
	}
	if (k > 7) {
		std::cout << "More than seven city cards on hand, you have to drop " << (k - 7) << "city cards" << std::endl;
	}
	for (auto& player : Board::instance().players()) {
		for (auto& card : player->cards()) {
			if (!card->isCityCard()) {
				std::cout << card->toString() << "\n";
			}
		}
	}

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

std::vector<PlayerCityCard*> Player::cityCards() const
{
	std::vector<PlayerCityCard*> cards;
	for (const auto& card : _cards)
	{
		if (card->isCityCard())
		{
			cards.push_back(static_cast<PlayerCityCard*>(card.get()));
		}
	}
	return cards;
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
	_role->printRole();
}