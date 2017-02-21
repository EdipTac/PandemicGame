#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Pawn.h"
#include <algorithm>
#include "PlayerCard.h"

class Player {
private:
	std::string _name;
	Pawn _pawn;
	std::vector<PlayerCard*> _cards;
	std::string _role;

public:
	// Constructor
	Player(const std::string name, const Pawn& pawn, const std::vector<PlayerCard*>& cards, const std::string role);
	// Default Constructor
	Player();


	// Accessors and Mutators
	std::vector<PlayerCard*> getCards();
	void addCard(PlayerCard* card);
	void removeCard(PlayerCard* card);

	Pawn getPawn() const;
	void setPawn(const Pawn& pawn);

	std::string getRole() const;
	void setRole(const std::string role);

	std::string getName() const;
	void setName(const std::string name);

	void displayCards();
};