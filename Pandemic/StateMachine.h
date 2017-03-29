#pragma once

#include <memory>

class State;

class StateMachine
{
public:
	void changeState(std::unique_ptr<State> newState);
	State* currentState() const;
	void update();

private:
	std::unique_ptr<State> _state;
};
