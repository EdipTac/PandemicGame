#include "ResilientPopulation.h"
#include "Player.h"
#include "Board.h"

const std::string desc = "Take a card from the Infection Discard Pile and remove it from the game.";


action::ResilientPopulation::ResilientPopulation(Player* const performer)
	: Action { "Resilient Population", desc, performer }
{}

void action::ResilientPopulation::solicitData()
{
	auto& player = *_performer;
	const auto& discardCards = Board::instance().infectionDeck().discardPile();
	//if the infectionDeck is empty, we cant throw a card
	if (Board::instance().infectionDeck().empty()) {
		std::cout << "You have no discarded infection cards. \n";
		return;
	}
	Board::instance().infectionDeck().printDiscards();

	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(discardCards.begin(), discardCards.end(), [&](const auto& C)
		{
			return input == c->name();
		});
		if (it != discardCards.end())
		{
			_target = input;
			break;
		}
		std::cout << "Not infection card of that name in the discard pile. \n";		
	}
}
void action::ResilientPopulation::perform()
{
	Board::instance().infectionDeck().deleteDiscard(_target);
}