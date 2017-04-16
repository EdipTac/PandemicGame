#pragma once

#include "Observable.h"
#include "Terminator.h"
#include "TerminationState.h"

class OutbreakCounter
	: public Terminator
{
public:
	OutbreakCounter();
	virtual TerminationState terminationState() const override;
	virtual std::string message() const override;
	size_t counter() const;
	void advance();
	void setCounter(int counter);

private:
	static const size_t _defaultLossCount;
	size_t _counter;
	size_t _lossCount;
};