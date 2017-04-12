#include "OutbreakCounter.h"

const size_t OutbreakCounter::_defaultLossCount = 8;

OutbreakCounter::OutbreakCounter()
	: _counter { 0 }
	, _lossCount { _defaultLossCount }
{}

TerminationState OutbreakCounter::terminationState() const
{
	return _counter > _lossCount ? TerminationState::Defeat : TerminationState::InProgress;
}

size_t OutbreakCounter::counter() const
{
	return _counter;
}

void OutbreakCounter::advance()
{
	++_counter;
	//notify();
}
