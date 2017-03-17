#pragma once

#include <vector>

#include "Observer.h"
#include "Terminator.h"

class TerminationObserver
	: public Observer
{
public:
	void subscribeTo(Terminator& subject);
	virtual void update() override;
	virtual void onVictory() = 0;
	virtual void onDefeat() = 0;

private:
	std::vector<Terminator*> _subjects;
};
