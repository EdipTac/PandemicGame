#pragma once
#include "Observer.h"
#include "Board.h"
class GameStatistics : public Observer {
public:
	GameStatistics();
	GameStatistics(Board &state);
	~GameStatistics();
	void update();
	void display();
private:
	Board *_state;
};

