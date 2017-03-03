// Implement a group of C++ classes that represent the player different 
// possession (e.g. pawn, reference cards, etc.). Write a driver program 
// that instantiates one player, and adds the possessions.Then implement
// classes for two concrete players.

#pragma once
#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include "Pawn.h"
#include <algorithm>

// Default Constructor
Player::Player()
	: _name(""), _pawn(Pawn()), _cards(std::vector<std::unique_ptr<PlayerCard>>()), _role("") {}
// Constructor
Player::Player(const std::string name, const Pawn& pawn, const std::vector<std::unique_ptr<PlayerCard>>& cards, const std::string role)
	: _name(name), _pawn(pawn), _cards(cards), _role(role) {}
// Copy Constructor
//Player::Player(const Player& player)
//	: Player() {}

// Accessors and Mutators
const std::vector<std::unique_ptr<PlayerCard>>& Player::getCards() const{
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
	for (std::vector<std::unique_ptr<PlayerCard>>::iterator i = _cards.begin(); i != _cards.end(); ++i) {
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
		
int main() {
	Player p1{};
	Player p2{};

	p1.setName("Player1");
	p1.setRole("Medic");
	p1.setPawn(Pawn("Atlanta", "Red"));
	std::unique_ptr<PlayerCard> c1 = std::make_unique<PCCity>("London");
	p1.addCard(std::move(c1));
	std::unique_ptr<PlayerCard> c2 = std::make_unique<PCEvent>("Helicopter", "Description");
	p1.addCard(std::move(c2));
	std::unique_ptr<PlayerCard> c3 = std::make_unique<PCCity>("Ho Chi Mihn City");
	p1.addCard(std::move(c3));

	p2.setName("Player2");
	p2.setRole("Researcher");
	p2.setPawn(Pawn("Montreal", "Green"));
	std::unique_ptr<PlayerCard> c4 = std::make_unique<PCCity>("Delhi");
	p2.addCard(std::move(c4));
	std::unique_ptr<PlayerCard> c5 = std::make_unique<PCCity>("Los Angeles");
	p2.addCard(std::move(c5));
	std::unique_ptr<PlayerCard> c6 = std::make_unique<PCEpidemic>();
	p2.addCard(std::move(c6));

	std::cout << "p1.name: " << p1.getName();
	std::cout << "\np1.role: " << p1.getRole();
	std::cout << "\np1.pawn: " << p1.getPawn().toString();
	p1.displayCards();

	std::cout << "\n\np2.name: " << p2.getName();
	std::cout << "\np2.role: " << p2.getRole();
	std::cout << "\np2.pawn: " << p2.getPawn().toString();
	p2.displayCards();

	std::system("pause");
}