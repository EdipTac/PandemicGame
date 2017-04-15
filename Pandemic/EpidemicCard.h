#pragma once

#include <string>

#include "PlayerCard.h"
#include "InfectionCardDeck.h"

// Represents an epidemic player card.
class EpidemicCard
	: public PlayerCard
{	
public:
	EpidemicCard();
	// Returns "EPIDEMIC"
	std::string name() const override;
	~EpidemicCard();
	// The rules of the epidemic card
	std::string description() const override;

	// Custom implementation of the inherited virtual function from PlayerCard
	virtual std::string toString();
	// Inherited via TextualCard
	virtual void onDraw(Board& state) override;
	// Inherited via PlayerCard
	virtual void cardWork(Deck<InfectionCard>& deck);
};