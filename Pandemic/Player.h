#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Pawn.h"
#include <algorithm>
#include "PlayerCard.h"

class Player {
private:
	// Attributes for Player objects
	std::string _name;
	Pawn _pawn;
	std::vector<PlayerCard*> _cards; // Must be a vector of pointers to PlayerCard to allow for use of derived classes (PCCity, PCEvent, PCEpidemic)
	std::string _role;

public:
	// Default Constructor
	Player();
	// Constructor
	Player(const std::string name, const Pawn& pawn, const std::vector<PlayerCard*>& cards, const std::string role);


	// Accessors and Mutators for _cards
	std::vector<PlayerCard*> cards();
	void addCard(PlayerCard* card);
	void removeCard(PlayerCard* card);

	// Accessors and Mutators for _pawn
	Pawn pawn() const;
	void setPawn(const Pawn& pawn);

	// Accessors and Mutators for _role
	std::string role() const;
	void setRole(const std::string role);

	// Accessors and Mutators for _name
	std::string name() const;
	void setName(const std::string name);

	// Print all of the cards in a Player's "hand"
	void displayCards();
};