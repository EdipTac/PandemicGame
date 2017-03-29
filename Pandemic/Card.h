#pragma once

#include <string>

class Board;

// Represents a single card of any type
class Card
{
public:
	// Destructor
	virtual ~Card() = 0;

	// The card's name
	virtual std::string name() const = 0;

	// The card's description
	virtual std::string description() const = 0;

	// The card's action when drawn
	virtual void onDraw(Board& state) = 0;
};