#pragma once

#include <vector>

#include "PolyObserver.h"
#include "Terminator.h"
#include "Board.h"

class TerminationHandler
	: public PolyObserver<Terminator>
{
public:
	virtual ~TerminationHandler();
	virtual void update() override;
	void quit();

protected:
	virtual void onVictory(const Terminator& t);
	virtual void onDefeat(const Terminator& t);
};
