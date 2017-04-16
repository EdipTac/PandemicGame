#pragma once

#include "Deck.h"
#include "PlayerCard.h"
#include "EpidemicCard.h"
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

	void addEpidemicToDeck(std::unique_ptr<EpidemicCard> card, size_t index, size_t numEpidemic);
};
