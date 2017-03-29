#include "StateMachine.h"
#include "State.h"

void StateMachine::changeState(std::unique_ptr<State> newState)
{
	if (_state)
	{
		_state->exit(*this);
	}

	_state = std::move(newState);

	if (_state)
	{
		_state->enter(*this);
	}
}

State* StateMachine::currentState() const
{
	return _state.get();
}

void StateMachine::update()
{
	if (_state)
	{
		_state->update(*this);
	}
}
