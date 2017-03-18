#pragma once

#include "TerminationHandler.h"

class GameState;

class DefaultTerminationHandler
	: public TerminationHandler
{
public:
	virtual ~DefaultTerminationHandler() override;
	virtual void onVictory() override;
	virtual void onDefeat() override;
};