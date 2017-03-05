#pragma once

#include "Pawn.h"
#include "Player.h"

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
const std::vector<std::unique_ptr<PlayerCard>>& Player::getCards() const{
	return _cards;
}
void Player::addCard(std::unique_ptr<PlayerCard> card) {
	_cards.push_back(std::move(card));
}

std::ostream& operator<<(std::ostream& os, PlayerCard& card)
{
	return os << card.toString();
}

void Player::displayCards() {
	std::cout << "\nDisplaying Cards: \n";
	for (auto i = _cards.begin(); i != _cards.end(); ++i) {
		std::cout << **i << "\n";
	}
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