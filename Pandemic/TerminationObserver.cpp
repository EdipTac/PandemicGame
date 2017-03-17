#include <algorithm>

#include "TerminationObserver.h"

void TerminationObserver::subscribeTo(Terminator& subject)
{
	subject.subscribe(*this);
	_subjects.push_back(&subject);
}

void TerminationObserver::update()
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
