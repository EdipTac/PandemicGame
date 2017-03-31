#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "Pawn.h"
#include "PlayerCard.h"
#include "RoleCard.h"


class PlayerCityCard;

// A player of the game
class Player
{
public:
	// Default Constructor
	Player();

	// Constructor
	Player(const std::string name, const Pawn& pawn, std::vector<std::unique_ptr<PlayerCard>>& cards, std::unique_ptr<RoleCard> role);

	std::string name() const;

	// Accessors and Mutators
	std::vector<PlayerCard*> cards() const;
	void addCard(std::unique_ptr<PlayerCard> card);
	void removeCardByName(const std::string& name);

	std::vector<PlayerCityCard*> cityCards() const;

	Pawn& pawn();
	const RoleCard& role() const;

	// Accessors and Mutators for _role
	//Prints the role of the player
	void displayRole();

	void setRole(std::unique_ptr<RoleCard> role);

	std::string getName() const;
	void setName(const std::string name);

	void displayCards();

	bool hasPositionCard();

	// True iff the player has a city card matching their pawn's position
	PlayerCard* positionCard();

	void giveCard(const PlayerCard& card, Player& recipient);

private:
	std::string _name;
	Pawn _pawn;
	// Must be a vector of pointers to PlayerCard to allow for use of derived classes (PlayerCityCard, Event, Epidemic)
	std::vector<std::unique_ptr<PlayerCard>> _cards;
	std::unique_ptr<RoleCard> _role;
};