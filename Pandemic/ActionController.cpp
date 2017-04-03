#include <iostream>
#include <sstream>

#include "ActionController.h"
#include "Action.h"
#include "CharterFlight.h"
#include "DirectFlight.h"
#include "DiscoverACure.h"
#include "DriveOrFerry.h"
#include "GiveKnowledge.h"
#include "Player.h"
#include "ShuttleFlight.h"
#include "TakeKnowledge.h"
#include "TreatDisease.h"

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
	_resetGeneralActions();
	_actions.clear();

	// General actions
	for (const auto& action : _generalActions)
	{
		_actions.push_back(action.get());
	}

	// Special role actions
	for (const auto& action : _player.role().actions())
	{
		_actions.push_back(action);
		_actions.back()->setPerformer(&_player);
	}
}

void ActionController::_resetGeneralActions()
{
	_generalActions.clear();
	_generalActions.push_back(_makeAction<DriveOrFerry>());
	_generalActions.push_back(_makeAction<DirectFlight>());
	_generalActions.push_back(_makeAction<ShuttleFlight>());
	_generalActions.push_back(_makeAction<CharterFlight>());
	_generalActions.push_back(_makeAction<TreatDisease>());
	_generalActions.push_back(_makeAction<DiscoverACure>());
	_generalActions.push_back(_makeAction<GiveKnowledge>());
	_generalActions.push_back(_makeAction<TakeKnowledge>());
}
