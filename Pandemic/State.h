#pragma once

class StateMachine;

class State
{
public:
	virtual ~State() = 0;
	virtual void enter(StateMachine& m) = 0;
	virtual void update(StateMachine& m) = 0;
	virtual void exit(StateMachine& m) = 0;
};
