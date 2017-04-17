#include "EpidemicCard.h"
#include "Board.h"

const std::string EPIDEMIC_DESCRIPTION =
	"1-Increase:\nMove the infection rate marker forward 1 space\n"
	"2-Infect:\nDraw the bottom card from the infection deck and put 3 cubes on that city. Discard that card\n"
	"3-Intensify:\nShuffle the cards in the infection discard pile and put them on top of the infection deck.\n\n";

EpidemicCard::EpidemicCard() {}

EpidemicCard:: ~EpidemicCard(){}

void EpidemicCard::onDraw(Board&) {}

std::string EpidemicCard::name() const
{
	return "EPIDEMIC";
}

std::string EpidemicCard::description() const
{
	return EPIDEMIC_DESCRIPTION;
}

void EpidemicCard::cardWork(Deck<InfectionCard>& deck)
{
	Board::instance().advanceInfectionCounter();//increase
	std::cout << "        -------        Epidemic !!!!!!!!        ------         " << "\nDraw for the bottom of the infection card deck: " << std::endl;
	
	if (!deck.empty())
	{
		auto temp = std::move(deck.drawTopCard());
		City& city = dynamic_cast <InfectionCard*> (temp.get())->city();
		std::cout << "Infection card : " << temp->name() << " with the colour of: " << colourName(city.colour()) << std::endl;
		std::cout << "Infects the city :" << temp->name() << " three times:" << std::endl;
		city.addDiseaseCubes(city.colour(), city.cubesBeforeOutbreak);//infect
		deck.addToDiscard(move(temp));//put to discard pile
	}

	// intensify
	deck.shuffleDiscards();
	while (!deck.emptyDiscard())
	{
		deck.addToDeck(deck.drawTopDiscard());
	}
}

bool EpidemicCard::isEpidemicCard() const
{
	return true;
}

PlayerCardType EpidemicCard::type() const
{
	return PlayerCardType::EpidemicCard;
}

std::string EpidemicCard::string(const size_t spacing) const
{
	return rawString();
}

std::string EpidemicCard::rawString() const
{
	return name();
}
