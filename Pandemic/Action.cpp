#include "Action.h"

action::Action::Action(const std::string& name, const std::string& description, Player* const performer)
	: _name { name }
	, _description { description }
	, performer { performer }
{}

action::Action::~Action() {}
