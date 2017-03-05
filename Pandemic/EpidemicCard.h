#pragma once
#include "PlayerCard.h"
#include <string>

// Epidemic class - represents PlayerCards of type Epidemic.
class EpidemicCard : public PlayerCard {
private:
	// Attribute for Epidemic objects, constant because all Epidemic cards are the same.
	
public:
	// Default Constructor
	EpidemicCard();

	// Accessor for EPIDEMIC_DESCRIPTION
	virtual std::string name() const override;
	virtual std::string description() const override;

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};