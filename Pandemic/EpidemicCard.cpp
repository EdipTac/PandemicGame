#include "EpidemicCard.h"

const std::string EPIDEMIC_DESCRIPTION =
	"1-Increase:\nMove the infection rate marker forward 1 space\n"
	"2-Infect:\nDraw the bottom card from the infection deck and put 3 cubes on that city. Discard that card\n"
	"3-Intensify:\nShuffle the cards in the infection discard pile and put them on top of the infection deck.\n\n";

std::string EpidemicCard::name() const
{
	return "EPIDEMIC";
}

std::string EpidemicCard::description() const
{
	return EPIDEMIC_DESCRIPTION;
}

std::string EpidemicCard::toString()
{
	return "Epidemic\n" + PlayerCard::toString() + ", Description: \n" + EPIDEMIC_DESCRIPTION;
}