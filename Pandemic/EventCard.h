#pragma once
#include <string>
#include "PlayerCard.h"

// Event class - represents PlayerCards of type Event.
class EventCard
	: public PlayerCard
{
public:
	// Constructor
	EventCard(std::string name, std::string description);

	// Accessor and Mutator for _description
	std::string name() const override;
	std::string description() const override;
	void setDescription(const std::string description);

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();

private:
	// Attributes for Event objects
	std::string _description;
	std::string _name;
};