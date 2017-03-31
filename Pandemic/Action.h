// Represents a single action that a player can take
// Default actions that all players can take are...

#pragma once

#include <string>

class Player;

namespace action
{
	class Action
	{
	public:
		// Constructs an action with a given name, description, and action performer
		Action(const std::string& name = "", const std::string& description = "", Player* const performer = nullptr);

		// Abstract
		virtual ~Action() = 0;

		// The name of the action
		std::string name() const;

		// Descriptive text
		std::string description() const;

		// Prepare action for performance
		virtual void solicitData() = 0;

		// Perform the action, if valid
		virtual void perform() = 0;

		// True iff the action can be completed - will consume an action
		virtual bool isValid() const = 0;

		// The player that is performing the action
		Player* performer;

	private:
		// The name of the action
		std::string _name;

		// Descriptive text
		std::string _description;
	};
}
