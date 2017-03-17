#include "OutbreakCounter.h"

const size_t OutbreakCounter::_defaultLossCount = 8;

OutbreakCounter::OutbreakCounter(const size_t _defaultLossCount)
	: _counter { 0 }
	, _lossCount { _defaultLossCount }
{}

TerminationState OutbreakCounter::terminationState()
{
	return _counter > _lossCount ? TerminationState::Defeat : TerminationState::InProgress;
}

void OutbreakCounter::advance()
{
	++_counter;
	notify();
}
