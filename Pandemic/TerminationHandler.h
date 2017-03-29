#pragma once

#include <vector>

#include "MultiView.h"
#include "Terminator.h"
#include "Board.h"

class TerminationHandler
	: public MultiView<Terminator>
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
