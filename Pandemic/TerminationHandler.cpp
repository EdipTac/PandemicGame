#include <algorithm>
#include <iostream>

#include "TerminationHandler.h"
#include "Board.h"

TerminationHandler::~TerminationHandler()
{
	for (const auto& subject : _subjects)
	{
		if (subject)
		{
			subject->unsubscribe(*this);
		}
	}
}

void TerminationHandler::update()
{
	using TS = TerminationState;
	for (const auto& subject : _subjects)
	{
		switch (subject->terminationState())
		{
			case TS::Victory:
				onVictory();
				return;
			case TS::Defeat:
				onDefeat();
				return;
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
