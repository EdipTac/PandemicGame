#include "ContingencyPlanner.h"
#include "StoreEventCard.h"
#include "UseStoredEventCard.h"

const std::string desc =
	"The Contingency Planner may, as an action, take an Event card from anywhere in the Player Discard Pile\n"
	"and place it on his Role card. Only 1 Event card can be on his role card at a time. It does not count \n"
	"against his hand limit. When the Contingency Planner plays the Event card on his role card remove this\n"
	"Event card from the game (instead of discarding it).";

role::ContingencyPlanner::ContingencyPlanner()
	: RoleCard { "Contingency Planner", desc, "Teal" }
{
	_actions.push_back(std::make_unique<action::StoreEventCard>(this));
	_actions.push_back(std::make_unique<action::UseStoredEventCard>(this));
}

role::ContingencyPlanner::~ContingencyPlanner() {}

void role::ContingencyPlanner::storeEventCard(std::unique_ptr<EventCard> card)
{
	_storedCard = std::move(card);
}

bool role::ContingencyPlanner::hasStoredEventCard() const
{
	return _storedCard != nullptr;
}

EventCard& role::ContingencyPlanner::storedEventCard() const
{
	return *_storedCard;
}

void role::ContingencyPlanner::deleteStoredEventCard()
{
	_storedCard.reset();
}
