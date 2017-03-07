#pragma once

#include <string>

#include "PlayerCard.h"

// Represents an epidemic player card.
class EpidemicCard
	: public PlayerCard
{	
public:
	// Returns "EPIDEMIC"
	virtual std::string name() const override;

	// The rules of the epidemic card
	virtual std::string description() const override;

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};