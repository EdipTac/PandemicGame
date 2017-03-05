#pragma once
#include <string>
#include "PlayerCard.h"

// Event class - represents PlayerCards of type Event.
class Event : public PlayerCard {
private:
	// Attributes for Event objects
	std::string _description;
public:
	// Default Constructor
	Event();
	// Constructor
	Event(std::string name, std::string description);

	// Accessor and Mutator for _description
	std::string description() const;
	void setDescription(const std::string description);

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};