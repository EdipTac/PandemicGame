#include <algorithm>
#include <iostream>

#include "TerminationHandler.h"
#include "Board.h"

TerminationHandler::~TerminationHandler() {}

void TerminationHandler::update()
{
	using TS = TerminationState;
	for (const auto& subject : _subjects)
	{
		if (subject->terminationState() == TS::Victory)
		{
			onVictory();
			break;
		}
		if (subject->terminationState() == TS::Defeat)
		{
			onDefeat();
			break;
		}
	}
}

void TerminationHandler::quit()
{
	_shouldQuit = true;
}

bool TerminationHandler::shouldQuit() const
{
	return _shouldQuit;
}

void TerminationHandler::onVictory()
{
	std::cout << "You win!" << std::endl;
	quit();
}

void TerminationHandler::onDefeat()
{
	std::cout << "You lose!" << std::endl;
	quit();
}
