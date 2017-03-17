#pragma once

#include "TerminationState.h"

// Interface
// A rule that ends the game
class Terminator
{
public:
	virtual ~Terminator() = 0;
	virtual TerminationState terminationState() = 0;
};
