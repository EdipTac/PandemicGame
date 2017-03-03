#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Pawn.h"
#include "PlayerCard.h"
#include "RoleCard.h"

class Player {
private:
	// Attributes for Player objects
	std::string _name;
	Pawn _pawn;
	std::vector<PlayerCard*> _cards; // Must be a vector of pointers to PlayerCard to allow for use of derived classes (PCCity, PCEvent, PCEpidemic)
	//std::string _role;
	std::unique_ptr < RoleCard > _role;

public:
	// Default Constructor
	Player();
	// Constructor
	//Player(const std::string name, const Pawn& pawn, const std::vector<PlayerCard*>& cards, const std::string role);  Jonny's old Player constructor 
	Player(const std::string name, const Pawn& pawn, const std::vector<PlayerCard*>& cards, const std::unique_ptr<RoleCard> role); //Edip's addition of Role card

	// Accessors and Mutators for _cards
	std::vector<PlayerCard*> cards();
	void addCard(PlayerCard* card);
	void removeCard(PlayerCard* card);

	// Accessors and Mutators for _pawn
	Pawn pawn() const;
	void setPawn(const Pawn& pawn);

	// Accessors and Mutators for _role  --> This was done by Jonny, keeping it here incase Edip's doesnt work
	//std::string role() const;
	//void setRole(const std::string role);

	//Prints the role of the player
	void displayRole();




	// Accessors and Mutators for _name
	std::string name() const;
	void setName(const std::string name);

	// Print all of the cards in a Player's "hand"
	void displayCards();
};