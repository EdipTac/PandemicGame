#pragma once

#include "Deck.h"
#include "EventCard.h"
#include "EpidemicCard.h"
#include "PlayerCard.h"
#include "Terminator.h"

class PlayerCardDeck
	: public Deck<PlayerCard>
	, public Terminator
{
public:
	// Dtor
	virtual ~PlayerCardDeck() override;

	virtual TerminationState terminationState() const override;
	virtual std::string message() const override;

	// Notifies on draw
	virtual std::unique_ptr<PlayerCard> drawTopCard() override;

	void addEpidemicCards(const size_t count);

	std::unique_ptr<EventCard> getFromDiscard(EventCard* const card);
};
