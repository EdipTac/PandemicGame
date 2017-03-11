#pragma once
#pragma warning(disable : 4100)

#include <string>

class GameState;

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
	virtual void onDraw(GameState& state) = 0;
};