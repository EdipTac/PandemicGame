#include "Action.h"
#include "ActionController.h"

action::Action::Action(const std::string& name, const std::string& description, Player* const performer)
	: _name { name }
	, _description { description }
	, _performer { performer }
{}

action::Action::~Action() {}

std::string action::Action::name() const
{
	return _name;
}

std::string action::Action::description() const
{
	return _description;
}

void action::Action::spendActionPoints(ActionController& ac) const
{
	ac.decrementActionPoints();
}

void action::Action::setPerformer(Player* const performer)
{
	_performer = performer;
}
