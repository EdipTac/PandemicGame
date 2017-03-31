#include "Action.h"

action::Action::Action(const std::string& name, const std::string& description, Player* const performer)
	: _name { name }
	, _description { description }
	, _performer { performer }
{}

action::Action::~Action() {}
