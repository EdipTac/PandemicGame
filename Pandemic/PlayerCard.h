#pragma once

#include <string>

#include "Card.h"

// Represents a player card
class PlayerCard
	: virtual public Card
{
public:
	// Destructor
	virtual ~PlayerCard() override = 0;

	// True iff the player card is also a city card
	virtual bool isCityCard() const;

	// virtual function that converts a PlayerCard object into an informative string.
	virtual std::string toString();
};