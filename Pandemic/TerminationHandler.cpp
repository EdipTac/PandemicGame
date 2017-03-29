#include <algorithm>
#include <iostream>

#include "TerminationHandler.h"
#include "GameState.h"

TerminationHandler::~TerminationHandler() {}

void TerminationHandler::update()
{
	using TS = TerminationState;
	const auto& hasTS = [](const TS& s)
	{
		return [&](const Terminator* const t)
		{
			return t->terminationState() == s;
		};
	};
	const auto& anyHasTS = [&](const TS& s)
	{
		return std::any_of(_subjects.begin(), _subjects.end(), hasTS(s));
	};
	
	if (anyHasTS(TS::Victory))
	{
		onVictory();
	}

	if (anyHasTS(TS::Defeat))
	{
		onDefeat();
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
