#pragma once
#include "PlayerCard.h"
#include <string>

// Epidemic class - represents PlayerCards of type Epidemic.
class Epidemic : public PlayerCard {
private:
	// Attribute for Epidemic objects, constant because all Epidemic cards are the same.
	const std::string EPIDEMIC_DESCRIPTION = "1-Increase:\nMove the infection rate marker forward 1 space\n2-Infect:\nDraw the bottom card from the infection deck and put 3 cubes on that city. Discard that card\n3-Intensify:\nShuffle the cards in the infection discard pile and put them on top of the infection deck.\n\n";
public:
	// Default Constructor
	Epidemic();

	// Accessor for EPIDEMIC_DESCRIPTION
	std::string getDescription() const;

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};