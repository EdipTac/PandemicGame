#include <algorithm>
#include <iostream>

#include "Board.h"
#include "TerminationHandler.h"
#include "Quit.h"

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
	throw Quit();
	//_shouldQuit = true;
}

bool TerminationHandler::shouldQuit() const
{
	return _shouldQuit;
}

void TerminationHandler::onVictory()
{
	throw Quit("You win!");
}

void TerminationHandler::onDefeat()
{
	throw Quit("You lose!");
}
