#pragma once

#include <memory>

class City;
class Player;

// Represents a player's pawn
class Pawn
{
public:
	// Constructs a pawn with a given owner
	Pawn(const Player& owner);

	// The pawn's owner
	const Player& owner() const;

	// The city the pawn is in
	City& position();

	// Sets the pawn to a new position
	Pawn& setPosition(City& position);

private:
	City* _position;
	const Player& _owner;
};
