#pragma once

#include <string>

#include "PlayerCard.h"
#include "TextualCard.h"

// Represents an Event player card
class EventCard
	: public TextualCard
	, public PlayerCard
{
public:
	// Constructs an event card with a given name and description
	EventCard(const std::string& name, const std::string& description);

	// Destructor
	~EventCard() override;

	// The name of the event card
	std::string name() const override;

	// The description of the event card
	std::string description() const override;

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();

	// Inherited via TextualCard
	virtual void onDraw(GameState& state) override;
};