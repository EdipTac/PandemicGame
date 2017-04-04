// Tracks and controls the number of actions a player is allowed each turn.
// Allows the general actions all players are allowed, as well as any specific actions granted by their role card.

#pragma once

#include <vector>
#include <memory>

#include "Action.h"

class Player;

class ActionController
{
public:
	// Construct an ActionController for a given player's turn.
	ActionController(Player& player);

	// Allow the player to select an action.
	void solicitAction();

	// True iff the player has any actions remaining for the turn.
	bool hasActionPoints();

	// Resets the actions for the next selection.
	void resetActionList();

private:
	Player& _player;
	size_t _actionPointsTotal;
	size_t _actionPointsRemaining;
	std::vector<std::unique_ptr<action::Action>> _generalActions;
	std::vector<action::Action*> _actions;

	void _resetGeneralActions();

	template <typename T>
	std::unique_ptr<T> _makeAction()
	{
		return std::make_unique<T>(&_player);
	}
};
