#pragma once
#include "Player.h"


// Default Constructor
Player::Player()
	: _name(""), _pawn(Pawn()), _cards(std::vector<std::unique_ptr<PlayerCard>>()), _role{ std::make_unique<RoleCard>() }  {}
// Constructor
Player::Player(const std::string name, const Pawn& pawn, std::vector<std::unique_ptr<PlayerCard>>& cards, std::unique_ptr<RoleCard> role)
	: _name(name), _pawn(pawn), _cards(std::move(cards)), _role(std::move(role)) {}

// Accessors and Mutators
const std::vector<std::unique_ptr<PlayerCard>>& Player::getCards() const {
	return _cards;
}
void Player::addCard(std::unique_ptr<PlayerCard> card) {
	_cards.push_back(std::move(card));
}
//void Player::removeCard(std::unique_ptr<PlayerCard> card) {
//	auto iter = find(_cards.begin(), _cards.end(), card);
//	if (iter != _cards.end()) { // the deck contains the card
//		_cards.erase(iter); // TODO: avoid a memory leak
//	}
//	else { // deck does not contain the card
//		std::cout << "Cannot remove card that doesn't exist!";
//	}
//}

std::ostream& operator<<(std::ostream& os, PlayerCard card)
{
	return os << card.toString();
}

void Player::displayCards() {
	std::cout << "\nDisplaying Cards: \n";
	for (auto i = _cards.begin(); i != _cards.end(); ++i) {
		std::cout << **i << "\n";
	}
}

Pawn Player::getPawn() const {
	return _pawn;
}
void Player::setPawn(const Pawn& pawn) {
	this->_pawn = pawn;
}

// Accessor for _role
//std::string Player::role() const {
//	return _role;
//}
// Mutator for _role
//void Player::setRole(const std::string role) {
//	this->_role = role;
//}

std::string Player::getName() const {
	return _name;
}
void Player::setName(const std::string name) {
	this->_name = name;
}

//display function for _role
void Player::displayRole() {
	_role->printRole();
}