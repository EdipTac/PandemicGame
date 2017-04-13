#pragma once

#include <string>
#include <memory>
#include "PlayerCard.h"
#include "TextualCard.h"
#include "Action.h"
using namespace action;

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
	virtual void onDraw(Board& state) override;

	// True
	virtual bool isEventCard() const override;

	virtual Action& ability();



private:
	std::unique_ptr<Action> _ability;
};