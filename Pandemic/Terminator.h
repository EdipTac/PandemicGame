#pragma once

#include "TerminationState.h"
#include "Observable.h"

// Interface
// A rule that ends the game
class Terminator
	: public Observable
{
public:
	virtual ~Terminator() = 0;
	virtual TerminationState terminationState() const = 0;
};
