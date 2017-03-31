#pragma once

#include <vector>
#include <memory>

#include "Action.h"

class Player;

class ActionController
{
public:
	ActionController(Player& player);
	void solicitAction();
	bool hasActionPoints();

private:
	Player& _player;
	size_t _actionPointsTotal;
	size_t _actionPointsRemaining;
	std::vector<std::unique_ptr<action::Action>> _actions;
};

