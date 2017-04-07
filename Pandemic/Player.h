#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "Deck.h"
#include "Pawn.h"
#include "PlayerCard.h"
#include "RoleCard.h"

class PlayerCityCard;
class EventCard;
class City;

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
	PlayerCard* getCard(const std::string& name);
	void discard(PlayerCard& card, Deck<PlayerCard>& deck);
	void discard(const std::string& name, Deck<PlayerCard>& deck);

	std::vector<PlayerCityCard*> cityCards() const;
	std::vector<EventCard*> eventCards() const;

	Pawn& pawn();
	const RoleCard& role() const;

	// Accessors and Mutators for _role
	// Prints the role of the player
	void displayRole();

	void setRole(std::unique_ptr<RoleCard> role);

	std::string getName() const;
	void setName(const std::string name);

	void displayCards();

	bool hasPositionCard();

	// Returns a pointer to a city card matching the player's position, if any. Returns nullptr otherwise.
	PlayerCard* positionCard();

	void giveCard(const PlayerCard& card, Player& recipient);

	void move(City& destination);

private:
	std::string _name;
	Pawn _pawn;
	// Must be a vector of pointers to PlayerCard to allow for use of derived classes (PlayerCityCard, Event, Epidemic)
	std::vector<std::unique_ptr<PlayerCard>> _cards;
	std::unique_ptr<RoleCard> _role;
};