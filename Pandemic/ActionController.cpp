#include <iostream>
#include <sstream>

#include "ActionController.h"
#include "DriveOrFerry.h"
#include "Player.h"

using namespace action;

constexpr size_t actionsTotalDefault = 4;

std::vector<std::unique_ptr<action::Action>> prepareActions(Player& player);

ActionController::ActionController(Player& player)
	: _player { player }
	, _actionPointsTotal { actionsTotalDefault }
	, _actionPointsRemaining { _actionPointsTotal }
	, _actions { prepareActions(_player) }
{}

void ActionController::solicitAction()
{
	std::cout << _player.name() << " has " << _actionPointsRemaining << " actions remaining.\n";
	std::stringstream ss;
	ss << "Please select an option:\n";
	for (size_t i = 0; i < _actions.size(); ++i)
	{
		ss << "\t(" << (i + 1) << ") " << _actions[i]->name() << "\n";
	}
	ss << ": ";
	std::cout << ss.str();

	int idx;
	while (true)
	{
		std::cin >> idx;
		std::cin.clear();
		std::cin.ignore();
		--idx;
		if (idx >= 0 && idx < _actions.size())
		{
			break;
		}
		std::cout << "Not a valid option.\n";
	}
	auto& action = *_actions[idx];

	action.solicitData();
	if (action.isValid())
	{
		--_actionPointsRemaining;
	}
}

bool ActionController::hasActionPoints()
{
	return _actionPointsRemaining > 0;
}

std::vector<std::unique_ptr<Action>> prepareActions(Player& player)
{
	std::vector<std::unique_ptr<Action>> actions;
	actions.push_back(std::make_unique<DriveOrFerry>(&player));
	return actions;
}