#pragma once

#include "Observable.h"
#include "Terminator.h"

class OutbreakCounter
	: public Observable
	, public Terminator
{

	virtual TerminationState terminationState() override;
};