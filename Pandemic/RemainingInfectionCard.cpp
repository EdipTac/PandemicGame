#pragma once
#include "RemainingInfectionCard.h"
#include <iostream>
using namespace std;

RemainingInfectionCard::RemainingInfectionCard(GameStatistics *dec)
	: StatisticDecorator(dec)
{
	Board::instance().subscribe(*this);
}
void RemainingInfectionCard::update() {

	RemainingInfectionCard::display();
}
void RemainingInfectionCard::display() {
	int black = 0; int blue = 0; int red = 0; int yellow = 0;
	for (const auto& card : Board::instance().infectionDeck().drawPile())
	{
		if ((colourAbbreviation(card->colour()) == "K"))
			black++;
		else if ((colourAbbreviation(card->colour()) == "B"))
			blue++;
		else if ((colourAbbreviation(card->colour()) == "R"))
			red++;
		else
			yellow++;
	}
	cout << "\nOn infection card deck there are:\n"<< blue << " blue disease infection card(s)" << "\n" << black << " black disease infection card(s)" << "\n" << red
		<< " red disease infection card(s)" << "\n" << yellow << " yellow disease infection card(s)\n\nUsed infection cards : " << endl;
	
	for (const auto& card : Board::instance().infectionDeck().discardPile())
	{  
		cout << card->name() << " " << colourName(card->colour()) << endl;
	}
	std::cout << "The remaining disease cubes to supply: " << "\nBlue: " <<
		(24 - Board::instance().diseaseCount(colourFromName("Blue")))<< "\nBlack: " <<
		(24 - Board::instance().diseaseCount(colourFromName("Black"))) << "\nRed: " <<
			(24 - Board::instance().diseaseCount(colourFromName("Red"))) << "\nYellow: " <<
			(24 - Board::instance().diseaseCount(colourFromName("Yellow"))) << "\n\n";

	cout << "\nInfection cards on deck (for test purpose) "<< "\n";

	for (const auto& card : Board::instance().infectionDeck().drawPile())
	{
		cout << card->name() << " " << colourName(card->colour()) << endl;
	}

};