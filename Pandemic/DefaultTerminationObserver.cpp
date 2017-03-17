#include <iostream>

#include "DefaultTerminationObserver.h"
#include "GameState.h"

DefaultTerminationObserver::DefaultTerminationObserver(GameState& gameState)
	: _gameState { &gameState }
{}

void DefaultTerminationObserver::onVictory()
{
	std::cout << "You win!" << std::endl;
	_gameState->quit();
}

void DefaultTerminationObserver::onDefeat()
{
	std::cout << "You lose!" << std::endl;
	_gameState->quit();
}
