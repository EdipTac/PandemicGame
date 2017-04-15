#pragma once

#include <string>
#include "Deck.h"
#include "Card.h"
#include "InfectionCard.h"

// Represents a player card
class PlayerCard
	: virtual public Card
{
public:
	// Destructor
	virtual ~PlayerCard() override = 0;

	// True iff the player card is also a city card
	virtual bool isCityCard() const;

	// True iff the card is an event card
	virtual bool isEventCard() const;

	// virtual function that converts a PlayerCard object into an informative string.
	virtual std::string toString();
	// virtual function for epidemic card
	virtual void cardWork(Deck<InfectionCard>& deck);
};