#include <iostream>
#include <sstream>

#include "ActionController.h"
#include "DriveOrFerry.h"
#include "GiveKnowledge.h"
#include "TakeKnowledge.h"
#include "DirectFlight.h"
#include "CharterFlight.h"
#include "Player.h"
#include "ShuttleFlight.h"
#include "TreatDisease.h"
#include "DiscoverACure.h"

using namespace action;

constexpr size_t actionsTotalDefault = 4;

ActionController::ActionController(Player& player)
	: _player { player }
	, _actionPointsTotal { actionsTotalDefault }
	, _actionPointsRemaining { _actionPointsTotal }
{
	resetActionList();
}

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
		action.perform();
	}
	resetActionList();
}

bool ActionController::hasActionPoints()
{
	return _actionPointsRemaining > 0;
}

void ActionController::resetActionList()
{
	_actions.clear();
	_actions.push_back(std::make_unique<DriveOrFerry>(&_player));
	_actions.push_back(std::make_unique<DirectFlight>(&_player));
	_actions.push_back(std::make_unique<ShuttleFlight>(&_player));
	_actions.push_back(std::make_unique<CharterFlight>(&_player));
	_actions.push_back(std::make_unique<TreatDisease>(&_player));
	_actions.push_back(std::make_unique<DiscoverACure>(&_player));
	_actions.push_back(std::make_unique<GiveKnowledge>(&_player));
	_actions.push_back(std::make_unique<TakeKnowledge>(&_player));
}
