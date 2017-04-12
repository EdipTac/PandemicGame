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
	bool shouldQuit() const;

protected:
	virtual void onVictory();
	virtual void onDefeat();
	void quit();

private:
	bool _shouldQuit = false;
};
