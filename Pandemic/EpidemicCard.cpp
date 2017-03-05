#include "EpidemicCard.h"

const std::string EPIDEMIC_DESCRIPTION =
	"1-Increase:\nMove the infection rate marker forward 1 space\n"
	"2-Infect:\nDraw the bottom card from the infection deck and put 3 cubes on that city. Discard that card\n3"
	"-Intensify:\nShuffle the cards in the infection discard pile and put them on top of the infection deck.\n\n";

// Default Constructor
//EpidemicCard::EpidemicCard()
//	: PlayerCard("EPIDEMIC") {}



std::string EpidemicCard::name() const
{
	return "EPIDEMIC";
}

// Accessor for EPIDEMIC_DESCRIPTION
std::string EpidemicCard::description() const
{
	return EPIDEMIC_DESCRIPTION;
}

// Custom implementation of the inherited virtual function from PlayerCard
std::string EpidemicCard::toString()
{
	return "Epidemic\n" + PlayerCard::toString() + ", Description: \n" + EPIDEMIC_DESCRIPTION;
}
