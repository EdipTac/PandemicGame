#pragma once

#include <string>
#include "Deck.h"
#include "Card.h"
#include "InfectionCard.h"

enum class PlayerCardType
{
	CityCard,
	EventCard,
	EpidemicCard
};

// Represents a player card
class PlayerCard
	: virtual public Card
{
public:
	// Destructor
	virtual ~PlayerCard() override = 0;

	// True iff the card is an event card
	virtual bool isEventCard() const;

	// True iff the card is an epidemic card
	virtual bool isEpidemicCard() const;

	// True iff the card can go in a player's hand
	bool isHandCard() const;

	// virtual function that converts a PlayerCard object into an informative string.
	virtual std::string string(const size_t spacing = 0) const = 0;
	virtual std::string rawString() const = 0;

	// virtual function for epidemic card
	virtual void cardWork(Deck<InfectionCard>& deck) = 0;

	virtual PlayerCardType type() const = 0;
};