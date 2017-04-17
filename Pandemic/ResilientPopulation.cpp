#include "ResilientPopulation.h"
#include "Player.h"
#include "Board.h"
#include "InfectionCard.h"
#include "MenuUtils.h"

const std::string desc = "Take a card from the Infection Discard Pile and remove it from the game.";


action::ResilientPopulation::ResilientPopulation(Player* const performer)
	: Action { "Resilient Population", desc, performer }
{}

void action::ResilientPopulation::solicitData()
{
	// Reset
	_target.clear();

	const auto& discardCards = Board::instance().infectionDeck().discardPile();
	//if the infectionDeck is empty, we cant throw a card
	if (Board::instance().infectionDeck().empty()) {
		std::cout << "You have no discarded infection cards. \n";
		return;
	}
	Board::instance().infectionDeck().printDiscards();

	_target =
		namedMenu(discardCards)
		.setMessage("Which card to remove: ")
		.solicitInput()->name();
}
void action::ResilientPopulation::perform()
{
	Board::instance().infectionDeck().deleteDiscard(_target);
}

bool action::ResilientPopulation::isValid() const
{
	return (!_target.empty());
}


