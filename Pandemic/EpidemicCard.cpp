#pragma warning(disable : 4100)	// To be removed

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

void EpidemicCard::onDraw(GameState& state) {}

//void EpidemicCard::epidemicInfect(InfectionCardDeck& deck, GameState& state)
//{
//	state.advanceInfectionCounter();//increase
//	std::cout << "Draw for the bottom of the infection card deck: " << std::endl;
//	std::unique_ptr<Card> temp = deck.drawBottomCard();
//	City& city = dynamic_cast <InfectionCard*> (temp.get())->city();
//	std::cout << "Infection card : " << temp->name() << " with the colour of: " << colourAbbreviation(city.colour()) << std::endl;
//	std::cout << "Infects the city :" << temp->name() << " three times:" << std::endl;
//	city.addDiseaseCubes(city.colour(), city.MAX_CUBE_PER_DISEASE, state);//infect
//	deck.reshuffleAndputback();// intensify
//}
