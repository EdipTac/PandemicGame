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
		Action(const std::string& name = "", const std::string& description = "", Player* const performer = nullptr);
		virtual ~Action() = 0;
		virtual void perform() = 0;
	private:
		Player* _performer;
		std::string _name;
		std::string _description;
	};
}
