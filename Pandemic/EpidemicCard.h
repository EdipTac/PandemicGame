#pragma once

#include <string>

#include "Deck.h"
#include "InfectionCard.h"
#include "PlayerCard.h"

// Represents an epidemic player card.
class EpidemicCard
	: public PlayerCard
{	
public:
	EpidemicCard();
	~EpidemicCard();

	// Returns "EPIDEMIC"
	std::string name() const override;
	// The rules of the epidemic card
	std::string description() const override;

	virtual void onDraw() override;
	virtual void cardWork(Deck<InfectionCard>& deck);

	virtual bool isEpidemicCard() const override;

	virtual PlayerCardType type() const override;

	virtual std::string string(const size_t spacing = 0) const override;
	virtual std::string rawString() const override;
};