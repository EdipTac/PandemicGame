#include "Epidemic.h"

// Default Constructor
Epidemic::Epidemic()
	: PlayerCard("EPIDEMIC") {}

// Accessor for EPIDEMIC_DESCRIPTION
std::string Epidemic::getDescription() const
{
	return EPIDEMIC_DESCRIPTION;
}

// Custom implementation of the inherited virtual function from PlayerCard
std::string Epidemic::toString()
{
	return "Epidemic\n" + PlayerCard::toString() + ", Description: \n" + EPIDEMIC_DESCRIPTION;
}
