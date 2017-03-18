#include "DefaultTerminationHandler.h"

#include "GameState.h"

DefaultTerminationHandler::~DefaultTerminationHandler() {}

void DefaultTerminationHandler::onVictory()
{
	std::cout << "You win!" << std::endl;
	quit();
}

void DefaultTerminationHandler::onDefeat()
{
	std::cout << "You lose!" << std::endl;
	quit();
}
