#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Pawn.h"
#include <algorithm>
#include "PlayerCard.h"
#include "RoleCard.h"

class Player {
private:
	std::string _name;
	Pawn _pawn;
	std::vector<PlayerCard*> _cards; // Must be a vector of pointers to PlayerCard to allow for use of derived classes (PCCity, PCEvent, PCEpidemic)
	//std::string _role;
	std::unique_ptr < RoleCard > _role;
public:
	// Default Constructor
	Player();
	// Constructor
	Player(const std::string name, const Pawn& pawn, std::vector<std::unique_ptr<PlayerCard>>& cards, std::unique_ptr<RoleCard> role);
	// Copy Constructor
	//Player(const Player& player);


	// Accessors and Mutators
	const std::vector<std::unique_ptr<PlayerCard>>& getCards() const;
	void addCard(std::unique_ptr<PlayerCard> card);
	//void removeCard(std::unique_ptr<PlayerCard> card);

	Pawn getPawn() const;
	void setPawn(const Pawn& pawn);

	// Accessors and Mutators for _role
	//std::string role() const;
	//void setRole(const std::string role);
	//Prints the role of the player
	void displayRole();

	std::string getName() const;
	void setName(const std::string name);

	void displayCards();
};