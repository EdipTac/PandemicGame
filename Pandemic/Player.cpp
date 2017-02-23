#pragma once
#include "Player.h"

// Default Constructor
Player::Player()
	: _name(""), _pawn(Pawn()), _cards(std::vector<PlayerCard*>()), _role("") {}
// Constructor
Player::Player(const std::string name, const Pawn& pawn, const std::vector<PlayerCard*>& cards, const std::string role)
	: _name(name), _pawn(pawn), _cards(cards), _role(role) {}


// Accessors for _cards
std::vector<PlayerCard*> Player::cards() {
	return _cards;
}
// Mutator for _cards -- adds a single card into the hand
void Player::addCard(PlayerCard* card) {
	_cards.push_back(card);
}
// Mutator for _cards -- removes a single card from the hand, if it exists
void Player::removeCard(PlayerCard* card) {
	auto iter = find(_cards.begin(), _cards.end(), card);
	if (iter != _cards.end()) { 
		// the deck contains the card
		_cards.erase(iter); // TODO: avoid a memory leak
	}
	else { 
		// deck does not contain the card
		std::cout << "Cannot remove card that doesn't exist!" << std::endl;
	}
}

// Overload the << operator for PlayerCard type. Needed in next method.
std::ostream& operator<<(std::ostream& os, PlayerCard* card)
{
	return os << card->toString();
}

// Prints all of the Player's cards, uses the overloaded << operator
void Player::displayCards() {
	std::cout << "\nDisplaying Cards: \n";
	for (std::vector<PlayerCard*>::iterator i = _cards.begin(); i != _cards.end(); ++i) {
		std::cout << *i << "\n";
	}
}

// Accessor for _pawn
Pawn Player::pawn() const {
	return _pawn;
}
// Mutator for _pawn
void Player::setPawn(const Pawn& pawn) {
	this->_pawn = pawn;
}

// Accessor for _role
std::string Player::role() const {
	return _role;
}
// Mutator for _role
void Player::setRole(const std::string role) {
	this->_role = role;
}

// Accessor for _name
std::string Player::name() const {
	return _name;
}
// Mutator for _name
void Player::setName(const std::string name) {
	this->_name = name;
}
		
// Main method - performs both the requirements for the Common Part and Part 3
int main() {
	// Constructing two players
	Player p1{};
	Player p2{};

	// Initializing attributes of p1, including PlayerCards
	p1.setName("Player1");
	p1.setRole("Medic");
	p1.setPawn(Pawn("Atlanta", "Red"));
	PlayerCard* c1 = new PCCity("London");
	p1.addCard(c1);
	PlayerCard* c2 = new PCEvent("Helicopter", "Fly any player directly to another city");
	p1.addCard(c2);
	PlayerCard* c3 = new PCCity("Ho Chi Mihn City");
	p1.addCard(c3);

	// Initializing attributes for p2, including PlayerCards
	p2.setName("Player2");
	p2.setRole("Researcher");
	p2.setPawn(Pawn("Montreal", "Green"));
	PlayerCard* c4 = new PCCity("Delhi");
	p2.addCard(c4);
	PlayerCard* c5 = new PCCity("Los Angeles");
	p2.addCard(c5);
	PlayerCard* c6 = new PCEpidemic();
	p2.addCard(c6);

	std::cout << "p1.name: " << p1.name();
	std::cout << "\np1.role: " << p1.role();
	std::cout << "\np1.pawn: " << p1.pawn().toString();
	p1.displayCards();

	std::cout << "\n\np2.name: " << p2.name();
	std::cout << "\np2.role: " << p2.role();
	std::cout << "\np2.pawn: " << p2.pawn().toString();
	p2.displayCards();

	std::system("pause");

	// Clean up Dynamic variables to avoid Memory Leak...
	delete(c1);
	delete(c2);
	delete(c3);
	delete(c4);
	delete(c5);
	delete(c6);
}