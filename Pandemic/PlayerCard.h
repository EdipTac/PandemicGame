#pragma once

#include <string>

#include "Card.h"

// PlayerCard class - base class for all different types of PlayerCards.
class PlayerCard
	: virtual public Card
{
public:
	// Default Constructor
	PlayerCard();
	virtual ~PlayerCard() override;

	// virtual function that converts a PlayerCard object into an informative string.
	virtual std::string toString();
};