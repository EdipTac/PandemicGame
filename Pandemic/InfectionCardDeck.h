//Header of InfectionCardDeck class
//InfectionCardDeck class represents infection card deck and discard infection card pile
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209

#pragma once

#include "Deck.h"
#include "InfectionCard.h"
#include "Terminator.h"

class InfectionCardDeck
	: public Deck<InfectionCard>
	, public Terminator
{
public:
	// Dtor
	virtual ~InfectionCardDeck() override;

	virtual TerminationState terminationState() const override;

	virtual std::unique_ptr<InfectionCard> drawTopCard() override;
};
