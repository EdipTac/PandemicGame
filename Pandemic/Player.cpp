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
	: _name(""), _pawn(Pawn()), _cards(std::vector<PlayerCard*>()), _role("") {}
// Constructor
Player::Player(const std::string name, const Pawn& pawn, const std::vector<PlayerCard*>& cards, const std::string role)
	: _name(name), _pawn(pawn), _cards(cards), _role(role) {}


// Accessors and Mutators
std::vector<PlayerCard*> Player::getCards() {
	return _cards;
}
void Player::addCard(PlayerCard* card) {
	_cards.push_back(card);
}
void Player::removeCard(PlayerCard* card) {
	auto iter = find(_cards.begin(), _cards.end(), card);
	if (iter != _cards.end()) { // the deck contains the card
		_cards.erase(iter); // TODO: avoid a memory leak
	}
	else { // deck does not contain the card
		std::cout << "Cannot remove card that doesn't exist!";
	}
}

std::ostream& operator<<(std::ostream& os, const PlayerCard* card)
{
	return os << card->PlayerCard::getName();
}

void Player::displayCards() {
	std::cout << "\nDisplaying Cards: \n";
	for (std::vector<PlayerCard*>::iterator i = _cards.begin(); i != _cards.end(); ++i) {
		std::cout << *i << " ";
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
	PlayerCard* c1;
	c1 = &(PlayerCard());
	c1->PlayerCard::setName("London"); // this prints
	p1.addCard(c1);
	PlayerCard* c2;
	c2 = &(PlayerCard("Helicopter")); // this doesn't
	p1.addCard(c2);
	PlayerCard* c3;
	c3 = &PlayerCard("Ho Chi Mihn City"); // this doesn't
	p1.addCard(c3);

	p2.setName("Player2");
	p2.setRole("Researcher");
	p2.setPawn(Pawn("Montreal", "Green"));
	PlayerCard* c4;
	c4 = &PlayerCard("Delhi");
	p2.addCard(c4);
	PlayerCard* c5;
	c5 = &PlayerCard("Los Angeles");
	p2.addCard(c5);
	PlayerCard* c6;
	c6 = &PlayerCard("Epidemic");
	p2.addCard(c6);

	std::cout << "p1.name: " << p1.getName();
	std::cout << "\np1.role: " << p1.getRole();
	std::cout << "\np1.pawn: " << p1.getPawn().toString();
	//PlayerCard test = *p1.getCards().front();
	//std::cout << "\nOldName: " << test.getName();
	//test.setName("newName");
	//std::cout << "\nNewName: " << test.getName();
	p1.displayCards();

	std::cout << "\n\np2.name: " << p2.getName();
	std::cout << "\np2.role: " << p2.getRole();
	std::cout << "\np2.pawn: " << p2.getPawn().toString();
	p2.displayCards();

	std::system("pause");
}