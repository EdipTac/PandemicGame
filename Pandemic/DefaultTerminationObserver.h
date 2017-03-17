#pragma once

#include "TerminationObserver.h"

class GameState;

class DefaultTerminationObserver
	: public TerminationObserver
{
public:
	DefaultTerminationObserver(GameState& gameState);

protected:
	virtual void onVictory() override;
	virtual void onDefeat() override;

private:
	GameState* _gameState;
};
