#include "UseStoredEventCard.h"

const std::string desc = "Play the stored Event Card and remove it from the game.";

action::UseStoredEventCard::UseStoredEventCard(Player* const performer, role::ContingencyPlanner* const roleCard)
	: Action { "Store Event Card", desc, performer }
	, _roleCard { roleCard }
{}

action::UseStoredEventCard::UseStoredEventCard(role::ContingencyPlanner* const roleCard)
	: UseStoredEventCard { nullptr, roleCard }
{}

void action::UseStoredEventCard::solicitData()
{
	// Nothing to do
}

void action::UseStoredEventCard::perform()
{
	auto& ability = _roleCard->storedEventCard().ability();
	ability.solicitData();
	if (ability.isValid())
	{
		ability.perform();
		_roleCard->deleteStoredEventCard();
	}
}

bool action::UseStoredEventCard::isValid() const
{
	return _roleCard && _roleCard->hasStoredEventCard();
}
