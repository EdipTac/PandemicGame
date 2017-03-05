#pragma once
#include <string>

// PlayerCard class - base class for all different types of PlayerCards.
class PlayerCard {
private:
	// Attributes for PlayerCard objects
	std::string _name;

public:
	// Default Constructor
	PlayerCard();
	// Constructor
	PlayerCard(std::string name);

	// Accessor and Mutators for _name
	std::string name() const;
	void setName(const std::string name);

	// virtual function that converts a PlayerCard object into an informative string.
	virtual std::string toString();
};