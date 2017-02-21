#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Pawn.h"
#include <algorithm>
#include "PlayerCard.h"
#include <memory>

class Player {
private:
	std::string _name;
	Pawn _pawn;
	std::vector<std::unique_ptr<PlayerCard>> _cards;
	std::string _role;

public:
	// Default Constructor
	Player();
	// Constructor
	Player(const std::string name, const Pawn& pawn, const std::vector<std::unique_ptr<PlayerCard>>& cards, const std::string role);
	// Copy Constructor
	//Player(const Player& player);


	// Accessors and Mutators
	std::vector<std::unique_ptr<PlayerCard>> getCards();
	void addCard(std::unique_ptr<PlayerCard> card);
	void removeCard(std::unique_ptr<PlayerCard> card);

	Pawn getPawn() const;
	void setPawn(const Pawn& pawn);

	std::string getRole() const;
	void setRole(const std::string role);

	std::string getName() const;
	void setName(const std::string name);

	void displayCards();
};