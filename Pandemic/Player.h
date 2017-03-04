#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "Pawn.h"
#include "PlayerCard.h"
#include "RoleCard.h"

//class Pawn;

class Player {
private:
	std::string _name;
	Pawn _pawn;
	// Must be a vector of pointers to PlayerCard to allow for use of derived classes (PCCity, PCEvent, PCEpidemic)
	std::vector<std::unique_ptr<PlayerCard>> _cards;
	std::unique_ptr<RoleCard> _role;
public:
	// Default Constructor
	Player();
	// Constructor
	Player(const std::string name, const Pawn& pawn, std::vector<std::unique_ptr<PlayerCard>>& cards, std::unique_ptr<RoleCard> role);


	// Accessors and Mutators
	const std::vector<std::unique_ptr<PlayerCard>>& getCards() const;
	void addCard(std::unique_ptr<PlayerCard> card);
	//void removeCard(std::unique_ptr<PlayerCard> card);

	Pawn& getPawn();
	const RoleCard& role() const;

	// Accessors and Mutators for _role
	//Prints the role of the player
	void displayRole();

	void setRole(std::unique_ptr<RoleCard> role);

	std::string getName() const;
	void setName(const std::string name);

	void displayCards();
};