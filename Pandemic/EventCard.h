#pragma once

#include <string>

#include "PlayerCard.h"
#include "TextualCard.h"

// Event class - represents PlayerCards of type Event.
class EventCard
	: public TextualCard
	, public PlayerCard
{
public:
	// Constructor
	EventCard(std::string name, std::string description);

	// Destructor
	~EventCard() override;

	std::string name() const override;
	std::string description() const override;

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};