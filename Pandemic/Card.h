#pragma once
#include "GameState.h"
#include <string>

// Represents a single card of any type
class Card
{
public:
	// Destructor
	virtual ~Card() = 0;
	virtual void cardWork(GameState&) = 0;
	// The card's name
	virtual std::string name() const = 0;

	// The card's description
	virtual std::string description() const = 0;
};