#pragma once

#include "Observable.h"
#include "Terminator.h"
#include "TerminationState.h"

class OutbreakCounter
	: public Terminator
{
public:
	OutbreakCounter(const size_t max = _defaultLossCount);
	virtual TerminationState terminationState() const override;
	void advance();

private:
	static const size_t _defaultLossCount;
	size_t _counter;
	size_t _lossCount;
};