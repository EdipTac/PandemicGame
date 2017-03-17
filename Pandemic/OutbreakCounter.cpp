#include "OutbreakCounter.h"

const size_t OutbreakCounter::_defaultLossCount = 8;

OutbreakCounter::OutbreakCounter(const size_t lossCount)
	: _counter { 0 }
	, _lossCount { lossCount }
{}

TerminationState OutbreakCounter::terminationState() const
{
	return _counter > _lossCount ? TerminationState::Defeat : TerminationState::InProgress;
}

void OutbreakCounter::advance()
{
	++_counter;
	notify();
}
