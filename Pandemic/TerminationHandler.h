#pragma once

#include <vector>

#include "MultiView.h"
#include "Terminator.h"
#include "GameState.h"

class TerminationHandler
	: public MultiView<Terminator>
{
public:
	TerminationHandler() {};
	TerminationHandler(const TerminationHandler&) = default;
	TerminationHandler& operator=(const TerminationHandler&) = default;
	virtual ~TerminationHandler();
	virtual void update() override;
	bool shouldQuit() const;

protected:
	virtual void onVictory() = 0;
	virtual void onDefeat() = 0;
	void quit();

private:
	bool _shouldQuit = false;
};
