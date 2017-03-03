#pragma once
#include "Player.h"

// Default Constructor
Player::Player()
	: _name(""), _pawn(Pawn()), _cards(std::vector<std::unique_ptr<PlayerCard>>()), _role("") {}
// Constructor
Player::Player(const std::string name, const Pawn& pawn, std::vector<std::unique_ptr<PlayerCard>>& cards, const std::string role)
	: _name(name), _pawn(pawn), _cards(std::move(cards)), _role(role) {}

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

std::string Player::getRole() const {
	return _role;
}
void Player::setRole(const std::string role) {
	this->_role = role;
}

std::string Player::getName() const {
	return _name;
}
void Player::setName(const std::string name) {
	this->_name = name;
}