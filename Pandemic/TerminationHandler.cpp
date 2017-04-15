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
				onVictory(*subject);
				return;
			case TS::Defeat:
				onDefeat(*subject);
				return;
		}
	}
}

void TerminationHandler::quit()
{
	//throw Quit();
	_shouldQuit = true;
}

bool TerminationHandler::shouldQuit() const
{
	return _shouldQuit;
}

void TerminationHandler::onVictory(const Terminator& t)
{
	throw Quit(t.message() + " You win!");
}

void TerminationHandler::onDefeat(const Terminator& t)
{
	throw Quit(t.message() + " You lose!");
}
