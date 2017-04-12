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
	cout << blue << " Remaining blue disease infection card(s)" << "\n" << black << " Remaining black disease infection card(s)" << "\n" << red
		<< " Remaining red disease infection card(s)" << "\n" << yellow << " Remaining yellow disease infection card(s)" << endl;

};