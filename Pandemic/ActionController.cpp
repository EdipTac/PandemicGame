#include <iostream>
#include <sstream>

#include "ActionController.h"
#include "Action.h"
#include "Board.h"
#include "BuildResearchStation.h"
#include "CharterFlight.h"
#include "DirectFlight.h"
#include "DiscoverACure.h"
#include "DriveOrFerry.h"
#include "GiveKnowledge.h"
#include "Player.h"
#include "ShuttleFlight.h"
#include "TakeKnowledge.h"
#include "TreatDisease.h"
#include "DoNothing.h"

using namespace action;

// Usually, a player gets four actions each turn.
constexpr size_t actionsTotalDefault = 4;

ActionController::ActionController(Player& player)
	: _player { player }
	, _actionPointsTotal { actionsTotalDefault }
	, _actionPointsRemaining { _actionPointsTotal }
{
	_generalActions.push_back(_makeAction<DriveOrFerry>());
	_generalActions.push_back(_makeAction<DirectFlight>());
	_generalActions.push_back(_makeAction<BuildResearchStation>());
	_generalActions.push_back(_makeAction<ShuttleFlight>());
	_generalActions.push_back(_makeAction<CharterFlight>());
	_generalActions.push_back(_makeAction<TreatDisease>());
	_generalActions.push_back(_makeAction<DiscoverACure>());
	_generalActions.push_back(_makeAction<GiveKnowledge>());
	_generalActions.push_back(_makeAction<TakeKnowledge>());
	_generalActions.push_back(_makeAction<DoNothing>());
	resetActionList();
}

void ActionController::solicitAction()
{
	std::cout << _player.name() << " has " << _actionPointsRemaining << " actions remaining.\n";

	// List available actions
	std::stringstream ss;
	ss << "Please select an option:\n";
	for (size_t i = 0; i < _actions.size(); ++i)
	{
		ss << "\t(" << (i + 1) << ") " << _actions[i]->name() << "\n";
	}
	ss << ": ";
	std::cout << ss.str();

	// Get an action index from the player
	int idx;
	while (true)
	{
		std::cin >> idx;
		std::cin.clear();
		std::cin.ignore();
		--idx;	// Action list is 1-based
		if (idx >= 0 && idx < _actions.size())
		{
			// Good choice
			break;
		}
		std::cout << "Not a valid option.\n"; // Bad choice
	}

	// Alias action
	auto& action = *_actions[idx];

	// Get additional data from player
	action.solicitData();
	if (action.isValid())
	{
		// If action can be completed, reduce action points appropriately
		action.spendActionPoints(*this);
		action.perform();
	}

	// Refresh
	resetActionList();
}

bool ActionController::hasActionPoints()
{
	return _actionPointsRemaining > 0;
}

void ActionController::resetActionList()
{
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

	// Shared actions
	for (const auto& player : Board::instance().players())
	{
		if (player == &Board::instance().currentPlayer())
		{
			continue;
		}
		for (const auto& action : player->role().actions())
		{
			_actions.push_back(action);
			_actions.back()->setPerformer(player);
		}
	}
}

void ActionController::decrementActionPoints()
{
	--_actionPointsRemaining;
}

void ActionController::zeroActionPoints()
{
	_actionPointsRemaining = 0;
}
