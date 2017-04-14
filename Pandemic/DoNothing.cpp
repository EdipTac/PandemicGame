#include "DoNothing.h"
#include "ActionController.h"

action::DoNothing::DoNothing(Player* const performer)
	: Action { "Do Nothing", "Skip the rest of your turn", performer }
{}

void action::DoNothing::solicitData() {}

void action::DoNothing::perform() {}

bool action::DoNothing::isValid() const
{
	return true;
}

void action::DoNothing::spendActionPoints(ActionController& ac) const
{
	ac.zeroActionPoints();
}
